#include <list>

#include "LevelGen.h"
#include "../Engine/NPC.h"
#include "../../Unuk/Player.h"

LevelGen::LevelGen(void) : _world(this) {
  _player = NULL;
}

LevelGen::~LevelGen(void) {

}

void LevelGen::New(void) {
  Unload();
  
  _world = WorldManager(this);
  
  levelWidth  = TILE_ARRAY_SIZE;
  levelHeight = TILE_ARRAY_SIZE;
  
  for(x = 0; x < levelWidth; x++) {
    for(y = 0; y < levelHeight; y++) {
      _tile[x][y].SetTileTextureName("grass");
      
      stringstream tilePath;
      tilePath << "../Data/Media/Images/Tiles/" << _tile[x][y].GetTileTextureName() << ".png";
      
      _tile[x][y].SetTileTexture(_tileTextures.Add(tilePath.str()));
      _tile[x][y].SetTileSolidity(false);
      _tile[x][y].SetTileXY(x * TILE_WIDTH, y * TILE_HEIGHT);
      _tile[x][y].SetEntitySolidity(false);
      _tile[x][y].SetZLevel(100);
    }
  }
  
  levelWidth  *= TILE_WIDTH;
  levelHeight *= TILE_HEIGHT;
  
  // procedural generation
	DoMagic();
}

void LevelGen::Load(const string& filename) {
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
        _tile[x][y].SetTileTextureName(dataElem->GetText());
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
          _tile[x][y].SetEntityTextureName(entityName);

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
  
  _world = WorldManager(this);
  
  GenerateEnemies();
}

void LevelGen::Save(const string& filename){
  TiXmlDocument doc;
  
  TiXmlElement* rootElem = new TiXmlElement("map");
  
  int levelWidthTiles   = levelWidth / TILE_WIDTH;
  int levelHeightTiles  = levelHeight / TILE_HEIGHT;
  
  for(y = 0; y < levelHeightTiles; y++) {
    TiXmlElement* lineElem = new TiXmlElement("line");
    
    for(x = 0; x < levelWidthTiles; x++) {
      TiXmlElement* tileElem = new TiXmlElement("tile");
      
      TiXmlElement* tileTextureElem = new TiXmlElement("tileTexture");
      TiXmlText* tileTextureText = new TiXmlText(_tile[x][y].GetTileTextureName().c_str());
      tileTextureElem->LinkEndChild(tileTextureText);
      
      TiXmlElement* solidTileElem = new TiXmlElement("solidTile");
      TiXmlText* solidTileText = new TiXmlText(_tile[x][y].GetTileSolidity() ? "true" : "false");
      solidTileElem->LinkEndChild(solidTileText);
      
      string entityTextureName = _tile[x][y].GetEntityTextureName();
      
      TiXmlElement* entityTextureElem = new TiXmlElement("entityTexture");
      TiXmlText* entityTextureText = new TiXmlText(entityTextureName.empty() ? "null" : entityTextureName.c_str());
      entityTextureElem->LinkEndChild(entityTextureText);
      
      TiXmlElement* solidEntityElem = new TiXmlElement("solidEntity");
      TiXmlText* solidEntityText = new TiXmlText(_tile[x][y].GetEntitySolitity() ? "true" : "false");
      solidEntityElem->LinkEndChild(solidEntityText);
      
      stringstream zLevelStr;
      zLevelStr << _tile[x][y].GetZLevel();
      
      TiXmlElement* zLevelElem = new TiXmlElement("zLevel");
      TiXmlText* zLevelText = new TiXmlText(zLevelStr.str().c_str());
      zLevelElem->LinkEndChild(zLevelText);
      
      tileElem->LinkEndChild(tileTextureElem);
      tileElem->LinkEndChild(solidTileElem);
      tileElem->LinkEndChild(entityTextureElem);
      tileElem->LinkEndChild(solidEntityElem);
      tileElem->LinkEndChild(zLevelElem);
      
      lineElem->LinkEndChild(tileElem);
    }
    
    rootElem->LinkEndChild(lineElem);
  }
  
  _currentMap = filename;
	string fullMapPath = "../Data/Media/Maps/" + filename;
  
  doc.LinkEndChild(rootElem);
  doc.SaveFile(fullMapPath.c_str());
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
  for(int x = 0; x < TILE_ARRAY_SIZE; x++) {
    for(int y = 0; y < TILE_ARRAY_SIZE; y++) {
      _tile[x][y] = MapTile(this);
    }
  }
}

void LevelGen::DoMagic(void) {
  GenerateEntities("tree", 25);
  GenerateEntities("hedge", 15);
  GenerateEntities("barrel", 40);
  GenerateEntities("barrel2", 100);
  GenerateEntities("stone", 35);
  GenerateEntities("stone2", 35);
  GenerateEntities("closedChest", 100); 
  GenerateEntities("closedChestMetal", 150); 
  GenerateEntities("closedChestMetal2", 250); 
  MakeWalkingPaths();
  GenerateEnemies();
}

void LevelGen::GenerateEntities(const string& name, int frequency) {
	int nextEntityGen = 1 + (rand() % frequency);
	std::string filename = "../Data/Media/Images/Entities/" + name + ".png";

	for(int x = 0; x < BOUNDARIES_X; x++) {
		for(int y = 0; y < BOUNDARIES_Y; y++) {
			nextEntityGen--;
			if(!_tile[x][y].GetTileSolidity() && !_tile[x][y].GetEntitySolitity() && nextEntityGen <= 0) {
				_tile[x][y].SetEntityTextureName(name);
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

	for(int x = 0; x < BOUNDARIES_X; x++) {
		bool pathFound = false;

		for(int y = 0; y < BOUNDARIES_Y; y++) {
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

void LevelGen::FindSpawnPoint(int& xArg, int& yArg, int objWidth, int objHeight) {
	xArg = rand() % (BOUNDARIES_X * TILE_WIDTH);
	yArg = rand() % (BOUNDARIES_Y * TILE_HEIGHT);
  
  if((xArg + objWidth + 1) > SCREEN_WIDTH) {
    xArg = SCREEN_WIDTH - objWidth - 1;
  }
  
  if((yArg + objHeight + 1) > SCREEN_HEIGHT) {
    yArg = SCREEN_HEIGHT - objHeight - 1;
  }
  
  SDL_Rect objRect;
  objRect.x = xArg;
  objRect.y = yArg;
  objRect.w = objWidth;
  objRect.h = objHeight;
  
  NPC* npc = _world.GetNPCAt(xArg, yArg);
  if(npc) {
    SDL_Rect npcRect;
    npcRect.x = npc->GetX();
    npcRect.y = npc->GetY();
    npcRect.w = npc->GetWidth();
    npcRect.h = npc->GetHeight();
    
    if(CheckCollisionRect(npcRect, objRect)) {
      FindSpawnPoint(xArg, yArg, objWidth, objHeight);
      return;
    }
  }
  
  for(int i = 0; i < BOUNDARIES_X; i++) {
    for(int j = 0; j < BOUNDARIES_Y; j++) {
      if(_tile[i][j].GetTileSolidity()) {
        FindSpawnPoint(xArg, yArg, objWidth, objHeight);
        return;
      }
      
      if(_tile[i][j].GetEntitySolitity()) {
        SDL_Rect entityRect;
        entityRect.x = _tile[i][j].GetEntityX();
        entityRect.y = _tile[i][j].GetEntityY();
        entityRect.w = _tile[i][j].GetEntityWidth();
        entityRect.h = _tile[i][j].GetEntityHeight(); 
        
        if(CheckCollisionRect(entityRect, objRect)) {
          FindSpawnPoint(xArg, yArg, objWidth, objHeight);
          return;
        }
      }
    }
  }
}

void LevelGen::GenerateEnemies(void) {
  int npcsToGen = 4 + (rand() % ((_player->GetLevel() * 2) + 4));
  
  for(int i = 0; i < npcsToGen; i++) {
    int spawnX;
    int spawnY;
    FindSpawnPoint(spawnX, spawnY, 40,45);
    
    _world.CreateNPC(spawnX, spawnY);
  }
}

void LevelGen::MoveIfPossible(Character* character, float xVel, float yVel, bool isPlayer) {
  if(xVel == 0.0f && yVel == 0.0f) {
    return;
  }
  
  int targetX = character->GetX() + xVel;
  int targetY = character->GetY() + yVel;
  
  if(targetX < 0 || targetX > (SCREEN_WIDTH - character->GetWidth()) || 
     targetY < 0 || targetY > (SCREEN_HEIGHT - character->GetHeight())) {
    return;
  }
  
  int targetTileX = targetX / TILE_WIDTH;
  int targetTileY = targetY / TILE_HEIGHT;
  
  if(_tile[targetTileX][targetTileY].GetTileSolidity()) {
    return;
  }
  
  SDL_Rect charRect;
  charRect.x = targetX;
  charRect.y = targetY + (character->GetHeight() / 4) * 3;
  charRect.w = character->GetWidth();
  charRect.h = character->GetHeight() / 4;
  
  for(int i = 0; i < BOUNDARIES_X; i++) {
    for(int j = 0; j < BOUNDARIES_Y; j++) {
      if(!_tile[i][j].GetEntitySolitity()) {
        continue;
      }
      
      SDL_Rect entityRect;
      entityRect.x = _tile[i][j].GetEntityX();
      entityRect.y = _tile[i][j].GetEntityY();
      entityRect.w = _tile[i][j].GetEntityWidth();
      entityRect.h = _tile[i][j].GetEntityHeight();
      
      if(CheckCollisionRect(entityRect, charRect)) {
        return;
      }
    }
  }
  
  if(_world.CheckCollision(charRect, character)) {
    return;
  }
  
  if(!isPlayer) {
    SDL_Rect playerRect;
    playerRect.x = _player->GetX();
    playerRect.y = _player->GetY();
    playerRect.w = _player->GetWidth();
    playerRect.h = _player->GetHeight();
    
    if(CheckCollisionRect(playerRect, charRect)) {
      return;
    }
  }
  
  character->SetXY(targetX, targetY);
}

bool LevelGen::CanMoveToPoint(int xArg, int yArg) {
  if(xArg < 0 || xArg > SCREEN_WIDTH || 
     yArg < 0 || yArg > SCREEN_HEIGHT) {
    return false;
  }
  
  int tileX = xArg / TILE_WIDTH;
  int tileY = yArg / TILE_HEIGHT;

  if(_tile[tileX][tileY].GetTileSolidity()) {
    return false;
  }
  
  for(int i = 0; i < BOUNDARIES_X; i++) {
    for(int j = 0; j < BOUNDARIES_Y; j++) {
      if(!_tile[i][j].GetEntitySolitity()) {
        continue;
      }
      
      SDL_Rect entityRect;
      entityRect.x = _tile[i][j].GetEntityX();
      entityRect.y = _tile[i][j].GetEntityY();
      entityRect.w = _tile[i][j].GetEntityWidth();
      entityRect.h = _tile[i][j].GetEntityHeight();
      
      if(xArg >= entityRect.x && xArg <= (entityRect.x + entityRect.w) &&
         yArg >= entityRect.y && yArg <= (entityRect.y + entityRect.h)) {
        return false;
      }
    }
  }

  return true;
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

MapTile& LevelGen::GetTile(int xArg, int yArg) {
  return _tile[xArg][yArg];
}
