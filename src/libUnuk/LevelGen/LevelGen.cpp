#include "LevelGen.h"
#include "../Engine/NPC.h"

LevelGen::LevelGen(void) {

}

LevelGen::~LevelGen(void) {

}

void LevelGen::Load(const string filename) {
  Unload();
  _currentMap = filename;
  string fullMapPath = "../Data/Media/Maps/" + filename;
  TiXmlDocument mapFile(fullMapPath.c_str());

  assert(mapFile.LoadFile() == true);

  // Getting dirty with some XML. This seems like a nicer
	// approach to loading maps, rather than parsing text files.
  TiXmlElement* rootElem = NULL;
  TiXmlElement* lineElem = NULL;
  TiXmlElement* tileElem = NULL;
  TiXmlElement* dataElem = NULL;

  x = -1;
  y = -1;

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
      x = -1;

      // <tile> - Then we will select the tile. and increment x to keep tiling that row.
      tileElem = lineElem->FirstChildElement("tile");
      assert(tileElem != NULL);
      while(tileElem) {
        x++;
        _tile[x][y].SetTileXY(x * TILE_WIDTH, y * TILE_HEIGHT);

        // <tileTexture> - Apply a teture to the tile.
        dataElem = tileElem->FirstChildElement("tileTexture");
        assert(dataElem != NULL);
        stringstream tilePath;
        tilePath << "../Data/Media/Images/Tiles/" << dataElem->GetText() << ".png";
        _tile[x][y].SetTileTexture(_tileTextures.Add(tilePath.str()));
        // <tileTexture> - Finished applying the texture, move to the next sibling.

        // <solidTile> - Check to see if the tile is solid or not.
        dataElem = dataElem->NextSiblingElement("solidTile");
        assert(dataElem != NULL);
        string tileSolidity = dataElem->GetText();
        assert(tileSolidity == "false" || tileSolidity == "true");
        if(tileSolidity == "false")
          _tile[x][y].SetTileSolidity(false);
        else
          _tile[x][y].SetTileSolidity(true);
        // </solidTile>

        // <entityTexture>
        dataElem = dataElem->NextSiblingElement("entityTexture");
        assert(dataElem != NULL);
        string entityName = dataElem->GetText();
        if(entityName != "null") {
          stringstream entityPath;
          entityPath << "../Data/Media/Images/Entities/" << entityName << ".png";
          _tile[x][y].SetEntityTexture(_entityTextures.AddAlpha(entityPath.str()));

          _tile[x][y].SetEntityXY(_tile[x][y].GetTileX() + TILE_WIDTH  / 2 - _tile[x][y].GetEntityWidth()  / 2,
                                   _tile[x][y].GetTileY() + TILE_HEIGHT / 2 - _tile[x][y].GetEntityHeight() / 2);
        }
        // </entityTexture>

        // <SolidEntity>
        dataElem = dataElem->NextSiblingElement("solidEntity");
        assert(dataElem != NULL);
        string entitySolidity = dataElem->GetText();
        assert(entitySolidity == "false" || entitySolidity == "true");
        if(entitySolidity == "false")
          _tile[x][y].SetEntitySolidity(false);
        else
          _tile[x][y].SetEntitySolidity(true);
        // </solidEntity>

        // <zlevel>
        dataElem = dataElem->NextSiblingElement("zLevel");
        assert(dataElem != NULL);
        _tile[x][y].SetZLevel(atoi(dataElem->GetText()));
        // </zlevel>

        // <mapTransition>
        dataElem = dataElem->NextSiblingElement("mapTransition");
        assert(dataElem != NULL);
        _tile[x][y].SetMapTransitionName(dataElem->GetText());
        // </mapTransition>

        // <mapTransX>
        dataElem = dataElem->NextSiblingElement("mapTransX");
        assert(dataElem != NULL);
        // int mapTransX = atoi(dataElem->GetText()); // not referenced
        // </mapTransX>

        // <mapTransY>
        dataElem = dataElem->NextSiblingElement("mapTransY");
        assert(dataElem != NULL);
       // int mapTransY = atoi(dataElem->GetText()); // not referenced
        // </mapTransY>

        tileElem = tileElem->NextSiblingElement("tile");
      }
      //</tile>

      lineElem = lineElem->NextSiblingElement("line");
    }
    // </line>
  }
  // </map>
  levelWidth  = x * TILE_WIDTH;
  levelHeight = y * TILE_HEIGHT;
  
  // procedural generation
  DoMagic();

  //character->Load(filename);

  NPC* npc = new NPC(this);
  
  int spawnX;
  int spawnY;

  //FindSpawnPoint(spawnX, spawnY);
  //npc->SetXY(spawnX, spawnY); // try to uncomment this, try to find out what's going on.. --konom
  npc->SetXY(100, 230);
  npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);
  _world.AddNPC(npc);

  npc = new NPC(this);
  //FindSpawnPoint(spawnX, spawnY);
  npc->SetXY(300, 250);
  npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);
  _world.AddNPC(npc);

  npc = new NPC(this);
  //FindSpawnPoint(spawnX, spawnY);
  npc->SetXY(400, 100);
  npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);
  _world.AddNPC(npc);
  
  npc = new NPC(this);
  //FindSpawnPoint(spawnX, spawnY);
  npc->SetXY(200, 400);
  npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);
  _world.AddNPC(npc);
  
  npc = new NPC(this);
  //FindSpawnPoint(spawnX, spawnY);
  npc->SetXY(250, 250);
  npc->LoadSprites("../Data/Media/Images/Characters/template.png", 40,45);
  _world.AddNPC(npc);
}

void LevelGen::Update(void) {
  _world.Update();
  // Update the map so we can render when camera moves.
}

void LevelGen::Render(void) {
  int xOrig = (camera.x / TILE_WIDTH) - 1;
  int yOrig = (camera.y / TILE_HEIGHT) - 1;

  if (xOrig < 0) xOrig = 0;
  if (yOrig < 0) yOrig = 0;

  int xEnd = xOrig + (SCREEN_WIDTH  / TILE_WIDTH) + 3;
  int yEnd = yOrig + (SCREEN_HEIGHT / TILE_HEIGHT) + 3;

  /* the fuck is this Allanis? --konom
  if(xEnd < x)
    xEnd++;
  else
    xEnd = x;

  if(yEnd < y)
    yEnd++;
  else
    yEnd = y;
  */

  if (xEnd > x) xEnd = x;
  if (yEnd > y) yEnd = y;
  if (xEnd < 0) xEnd = 0;
  if (yEnd < 0) yEnd = 0;

  if (xOrig > xEnd) xOrig = xEnd - 1;
  if (yOrig > yEnd) yOrig = yEnd - 1;

  for(int i = xOrig; i < xEnd; i++) {
    for(int j = yOrig; j < yEnd; j++) {
      _tile[i][j].Render();
    }
  }

  _world.Render();
}

void LevelGen::Unload(void) {
  _tileTextures.Unload();
  _entityTextures.Unload();
}

void LevelGen::DoMagic(void) {
    GenerateEntities("tree", 25);
    GenerateEntities("hedge", 15);
    GenerateEntities("barrel", 40);
    MakeWalkingPaths();
}

void LevelGen::GenerateEntities(const string& name, int frequency) {
  int nextEntityGen = 1 + (rand() % frequency);
  std::string filename = "../Data/Media/Images/Entities/" + name + ".png";

  for(int x = 0; x < SCREEN_WIDTH/64 + 1; x++) {
    for(int y = 0; y < SCREEN_HEIGHT/64; y++) {
      nextEntityGen--;
      if(!_tile[x][y].GetTileSolidity() && !_tile[x][y].GetEntitySolitity() && nextEntityGen <= 0) {
        _tile[x][y].SetEntityTexture(_entityTextures.AddAlpha(filename));
              
        _tile[x][y].SetEntityXY(_tile[x][y].GetTileX() + TILE_WIDTH  / 2 - _tile[x][y].GetEntityWidth()  / 2,
                                _tile[x][y].GetTileY() + TILE_HEIGHT / 2 - _tile[x][y].GetEntityHeight() / 2);
                
        _tile[x][y].SetEntitySolidity(true);
                
        nextEntityGen =  1 + (rand() % frequency);
      }
    }
  }
}

void LevelGen::MakeWalkingPaths(void) {
  int lastOpenY = rand() % 5;
  
  for(int x = 0; x < SCREEN_WIDTH/64 + 1; x++) {
    bool pathFound = false;
    
    for(int y = 0; y < SCREEN_HEIGHT/64; y++) {
      if(!_tile[x][y].GetEntitySolitity()) {
        pathFound = true;
        break;
      } else {
        lastOpenY = y;
      }
    }
    
    if(!pathFound) {
      _tile[x][lastOpenY].SetEntityTexture(NULL);
      _tile[x][lastOpenY].SetEntitySolidity(false);
    }
  }
}

void LevelGen::FindSpawnPoint(int& xArg, int& yArg) {
  xArg = rand() % SCREEN_WIDTH;
  yArg = rand() % SCREEN_HEIGHT;
    
  int tileX = xArg / 64;
  int tileY = yArg / 64;
  
  if(!_tile[tileX][tileY].GetEntitySolitity() && !_world.HasNPCIn(xArg, yArg)) {
      return;
  }
  
  FindSpawnPoint(xArg, yArg);
}

string LevelGen::GetCurrentMap(void) {
  return _currentMap;
}

bool LevelGen::GetTileSolidity(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetTileSolidity();
}

int LevelGen::GetTileX(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetTileX();
}

int LevelGen::GetTileY(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetTileY();
}

bool LevelGen::GetEntitySolidity(int xArg, int yArg) {
  if(xArg > x || yArg > y || yArg < 0 || yArg < 0) {
    return false;
  }

  return _tile[xArg + 1][yArg + 1].GetEntitySolitity();
}

int LevelGen::GetEntityX(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetEntityX();
}

int LevelGen::GetEntityY(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetEntityY();
}

int LevelGen::GetEntityWidth(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetEntityWidth();
}

int LevelGen::GetEntityHeight(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetEntityHeight();
}

int LevelGen::GetTileZLevel(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetZLevel();
}

string LevelGen::GetMapTransitionName(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetMapTransitionName();
}

int LevelGen::GetMapTransitionX(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetMapTransitionX();
}

int LevelGen::GetMapTransitionY(int xArg, int yArg) {
  return _tile[xArg + 1][yArg + 1].GetMapTransitionY();
}
