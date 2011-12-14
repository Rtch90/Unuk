#include "Map.h"

Map::Map(void) {

}

Map::~Map(void) {

}

void Map::Load(const string filename) {
  Unload();
  m_currentMap = filename;
  string fullMapPath = "../Data/Media/Maps/" + filename;
  TiXmlDocument mapFile(fullMapPath);

  assert(mapFile.LoadFile() == true);

  // Getting dirty with some XML. This seems like a nicer
  // approach to loading maps, rather than parsing tet files.
  TiXmlElement* rootElem = NULL;
  TiXmlElement* lineElem = NULL;
  TiXmlElement* tileElem = NULL;
  TiXmlElement* dataElem = NULL;

  // We will set x and y positions to zero for now, as we
  // are going to set them withing the XML file.
  x = 0;
  y = 0;

  // <map> - Let's start parsing the map.
  rootElem = mapFile.FirstChildElement("map");
  assert(rootElem != NULL);
  if(rootElem) {
    // <line> - We want to tile one line at a time. line represents
    // the row we are tiling.
    lineElem = rootElem->FirstChildElement("line");
    assert(lineElem != NULL);
    while(lineElem) {
      y++;
      x = 0;

      // <tile> - Then we will select the tile. and increment x to keep tiling that row.
      tileElem = lineElem->FirstChildElement("tile");
      assert(tileElem != NULL);
      while(tileElem) {
        x++;
        m_tile[x][y].SetTileXY((x - 1) * TILE_WIDTH, (y - 1) * TILE_HEIGHT);

        // <tileTexture> - Apply a teture to the tile.
        dataElem = tileElem->FirstChildElement("tileTexture");
        assert(dataElem != NULL);
        stringstream tilePath;
        tilePath << "../Data/Media/Images/Tiles/" << dataElem->GetText() << ".png";
        m_tile[x][y].SetTileTexture(m_tileTextures.Add(tilePath.str()));
        // <tileTexture> - Finished applying the texture, move to the next sibling.

        // <solidTile> - Check to see if the tile is solid or not.
        dataElem = dataElem->NextSiblingElement("solidTile");
        assert(dataElem != NULL);
        string tileSolidity = dataElem->GetText();
        assert(tileSolidity == "false" || tileSolidity == "true");
        if(tileSolidity == "false")
          m_tile[x][y].SetTileSolidity(false);
        else
          m_tile[x][y].SetTileSolidity(true);
        // </solidTile>

        // <entityTexture>
        dataElem = dataElem->NextSiblingElement("entityTexture");
        assert(dataElem != NULL);
        string entityName = dataElem->GetText();
        if(entityName == "null")
          m_tile[x][y].SetEntityTexture(NULL);
        else {
          stringstream entityPath;
          entityPath << "../Data/Media/Images/Entities/" << entityName << ".png";
          m_tile[x][y].SetEntityTexture(m_entityTextures.AddAlpha(entityPath.str()));

          m_tile[x][y].SetEntityXY(m_tile[x][y].GetTileX() + TILE_WIDTH  / 2 - m_tile[x][y].GetEntityWidth()  / 2,
                                   m_tile[x][y].GetTileY() + TILE_HEIGHT / 2 - m_tile[x][y].GetEntityHeight() / 2);
        }
        // </entityTexture>

        // <SolidEntity>
        dataElem = dataElem->NextSiblingElement("solidEntity");
        assert(dataElem != NULL);
        string entitySolidity = dataElem->GetText();
        assert(entitySolidity == "false" || entitySolidity == "true");
        if(entitySolidity == "false")
          m_tile[x][y].SetEntitySolidity(false);
        else
          m_tile[x][y].SetEntitySolidity(true);
        // </solidEntity>

        // <zlevel>
        dataElem = dataElem->NextSiblingElement("zlevel");
        assert(dataElem != NULL);
        m_tile[x][y].SetZLevel(atoi(dataElem->GetText()));
        // </zlevel>

        // <mapTransition>
        dataElem = dataElem->NextSiblingElement("mapTransition");
        assert(dataElem != NULL);
        m_tile[x][y].SetMapTransitionName(dataElem->GetText());
        // </mapTransition>

        // <mapTransX>
        dataElem = dataElem->NextSiblingElement("mapTransX");
        assert(dataElem != NULL);
        int mapTransX = atoi(dataElem->GetText());
        // </mapTransX>

        // <mapTransY>
        dataElem = dataElem->NextSiblingElement("mapTransY");
        assert(dataElem != NULL);
        int mapTransY = atoi(dataElem->GetText());
        // </mapTransY>

        tileElem = tileElem->NextSiblingElement("tile");
      }
      //</tile>

      lineElem = lineElem->NextSiblingElement("line");
    }
    // </line>
  }
  // </map>
  levelWidth  = (x - 1)  * TILE_WIDTH;
  levelHeight = (y - 1)  * TILE_HEIGHT;

  //character->Load(filename);
}

void Map::Render(void) {
  for(int j = 1; j < x; j++)
    for(int i = 1; i < y; i++) {
    ApplySurface(m_tile[j][i].GetTileX(), m_tile[j][i].GetTileY(), m_tile[j][i].GetTileTexture(), screen);

    if(m_tile[j][i].GetEntityTexture() != NULL)
      ApplySurface(m_tile[j][i].GetEntityX(), m_tile[j][i].GetEntityY(), m_tile[j][i].GetEntityTexture(), screen);
  }
  return;

  int xOrig = (camera.x / TILE_WIDTH)  + 1;
  int yOrig = (camera.y / TILE_HEIGHT) + 1;

  int xEnd = xOrig + (SCREEN_WIDTH / TILE_WIDTH);
  int yEnd = yOrig + (SCREEN_HEIGHT / TILE_HEIGHT);

  if(xEnd < x)
    xEnd++;
  if(yEnd < y)
    yEnd++;

  for(int j = 1; j < xEnd; j++)
  for(int i = 1; i < yEnd; i++) {
    ApplySurface(m_tile[j][i].GetTileX(), m_tile[j][i].GetTileY(),
                 m_tile[j][i].GetTileTexture(), screen);
    if(m_tile[j][i].GetEntityTexture() != NULL) {
      Debug::logger->message("Entity");
      ApplySurface(m_tile[j][i].GetEntityX(), m_tile[j][i].GetEntityY(),
                   m_tile[j][i].GetEntityTexture(), screen);
    }
  }
}

void Map::Unload(void) {
  m_tileTextures.Unload();
  m_entityTextures.Unload();

  for(int i = 0; i < TILE_ARRAY_SIZE; i++) {
    for(int j = 0; j < TILE_ARRAY_SIZE; j++) {
      m_tile[i][j].SetTileTexture(NULL);
      m_tile[i][j].SetTileSolidity(false);
      m_tile[i][j].SetEntityTexture(NULL);
      m_tile[i][j].SetEntitySolidity(false);
      m_tile[i][j].SetMapTransitionName("null");
    }
  }
}

string Map::GetCurrentMap(void) {
  return m_currentMap;
}

bool Map::GetTileSolidity(int row, int column) {
  return m_tile[row + 1][column + 1].GetTileSolidity();
}

int Map::GetTileX(int row, int column) {
  return m_tile[row + 1][column + 1].GetTileX();
}

int Map::GetTileY(int row, int column) {
  return m_tile[row + 1][column + 1].GetTileY();
}

bool Map::GetEntitySolidity(int row, int column) {
  return m_tile[row + 1][column + 1].GetEntitySolitity();
}

int Map::GetEntityX(int row, int column) {
  return m_tile[row + 1][column + 1].GetEntityX();
}

int Map::GetEntityY(int row, int column) {
  return m_tile[row + 1][column + 1].GetEntityY();
}

int Map::GetEntityWidth(int row, int column) {
  return m_tile[row + 1][column + 1].GetEntityWidth();
}

int Map::GetEntityHeight(int row, int column) {
  return m_tile[row + 1][column + 1].GetEntityHeight();
}

int Map::GetTileZLevel(int row, int column) {
  return m_tile[row + 1][column + 1].GetZLevel();
}

string Map::GetMapTransitionName(int row, int column) {
  return m_tile[row + 1][column + 1].GetMapTransitionName();
}

int Map::GetMapTransitionX(int row, int column) {
  return m_tile[row + 1][column + 1].GetMapTransitionX();
}

int Map::GetMapTransitionY(int row, int column) {
  return m_tile[row + 1][column + 1].GetMapTransitionY();
}
