#include "Map.h"

Map::Map(void) {
  m_tileTextures = new TextureManager;
  m_entityTextures = new TextureManager;
  //m_characters = CharacterManager;
}

Map::~Map(void) {
  delete m_tileTextures;
  delete m_entityTextures;
  //delete m_characters;
}

void Map::Load(const string filename) {
  m_currentMap = filename;
  string fullMapPath = "../Data/Media/Maps/" + filename;
  ifstream mapFile(fullMapPath.c_str());
  assert(mapFile.is_open());

  Unload();

  // Read in from the map file, one line at a time.
  string line;
  while(getline(mapFile, line)) {
    m_mapRows = 1;

    istringstream iss(line);

    string tileName;
    while(iss >> tileName) {
      string fullTilePath = "../Data/Media/Images/Tiles/" + tileName + ".png";
      m_tile[m_mapRows][m_mapColumns].SetTextureID(m_tileTextures->Add(fullTilePath));

      // Read the file solidity.
      bool tileSolidity;
      iss >> tileSolidity;
      m_tile[m_mapRows][m_mapColumns].SetTileSolidity(tileSolidity);

      // Set the tile x and y variable.
      m_tile[m_mapRows][m_mapColumns].SetTileXY((m_mapRows - 1) * TILE_WIDTH, (m_mapColumns - 1) * TILE_HEIGHT);

      // Read the entity textures.
      string entityName;
      iss >> entityName;

      if(entityName == "n") {
        m_tile[m_mapRows][m_mapColumns].SetEntityID(-1);
      } else {
        string entityPath = "../Data/Media/Images/Entities/" + entityName + ".png";

        m_tile[m_mapRows][m_mapColumns].SetEntityID(m_entityTextures->AddAlpha(entityPath));

        // Set the entities width and height variables.
        m_tile[m_mapRows][m_mapColumns].SetEntityWidthHeight(
            m_entityTextures->GetTextureWidth(m_tile[m_mapRows][m_mapColumns].GetEntityID()),
            m_entityTextures->GetTextureHeight(m_tile[m_mapRows][m_mapColumns].GetEntityID()));

        // Set the entities x and y variables.
        m_tile[m_mapRows][m_mapColumns].SetEntityXY(
            m_tile[m_mapRows][m_mapColumns].GetTileX() - (m_tile[m_mapRows][m_mapColumns].GetEntityWidth()  / 2 + TILE_WIDTH  / 2),
            m_tile[m_mapRows][m_mapColumns].GetTileY() - (m_tile[m_mapRows][m_mapColumns].GetEntityHeight() / 2 + TILE_HEIGHT / 2));
      }
      // Read the entity solidity.
      bool entitySolidity;
      iss >> entitySolidity;
      m_tile[m_mapRows][m_mapColumns].SetEntitySolidity(entitySolidity);

      // Read the tile zlevel.
      int zLevel;
      iss >> zLevel;
      m_tile[m_mapRows][m_mapColumns].SetZLevel(zLevel);

      // Read the map transition value.
      string mapTransitionName;
      iss >> mapTransitionName;
      m_tile[m_mapRows][m_mapColumns].SetMapTransitionName(mapTransitionName);

      // Read the transition x and y.
      int mapTransitionX, mapTransitionY;
      iss >> mapTransitionX;
      iss >> mapTransitionY;
      m_tile[m_mapRows][m_mapColumns].SetMapTransitionXY(mapTransitionX, mapTransitionY);

      m_mapRows++;
      assert(m_mapRows < TILE_ARRAY_SIZE);
    }
    m_mapColumns++;
    assert(m_mapColumns < TILE_ARRAY_SIZE);
  }
  levelWidth  = (m_mapRows - 1)     * TILE_WIDTH;
  levelHeight = (m_mapColumns - 1)  * TILE_HEIGHT;

  //character->Load(filename);
}

// TODO: Take the camera into account so we do not
// draw things off of screen.
void Map::Render(void) {
  for(int j = 1; j < m_mapRows; j++)
    for(int i = 1; i < m_mapColumns; i++) {
    ApplySurface(m_tile[j][i].GetTileX(), m_tile[j][i].GetTileY(),
                 m_tileTextures->Get(m_tile[j][i].GetTextureID()), screen);
    if(m_tile[j][i].GetEntityID() != -1) {
      ApplySurface(m_tile[j][i].GetEntityX(), m_tile[j][i].GetEntityY(),
                   m_entityTextures->Get(m_tile[j][i].GetEntityID()), screen);
    }
  }
}

void Map::Unload(void) {
  m_tileTextures->Clear();
  m_entityTextures->Clear();

  // Start at 1,1 so we do not have to be concerned about messy
  // bounds checking when accessing the tile array within the game loop.
  m_mapRows     = 1;
  m_mapColumns  = 1;

  // As we are not doing bounds checking inside the game loop
  // we don't want there to be a solid entity with w,h of ($RAND)
  // creating an invisible wall anywhere.
  for(int i = 0; i < TILE_ARRAY_SIZE; i++) {
    for(int j = 0; j < TILE_ARRAY_SIZE; j++) {
      m_tile[i][j].SetTileSolidity(false);
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
