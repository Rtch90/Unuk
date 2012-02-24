#include <list>

#include "LevelGen.h"
#include "../Engine/NPC.h"
#include "../System/Serialiser.h"
#include "../../Unuk/Player.h"

LevelGen::LevelGen(void) : _world(this) {
  _player = NULL;
}

LevelGen::~LevelGen(void) {

}

void LevelGen::New(void) {
  Unload();
  
  _world = WorldManager(this);

  for(x = 0; x < TILE_ARRAY_WIDTH; x++) {
    for(y = 0; y < TILE_ARRAY_HEIGHT; y++) {
      _tile[x][y].SetTileTextureName("grass");
      
      stringstream tilePath;
      tilePath << "../Data/Media/Images/Tiles/" << _tile[x][y].GetTileTextureName() << ".png";
      
      _tile[x][y].SetTileTexture(_tileTextures.Add(tilePath.str()));
      _tile[x][y].SetTileSolidity(false);
      _tile[x][y].SetTileXY(x * TILE_WIDTH, y * TILE_HEIGHT);
      _tile[x][y].SetEntitySolidity(false);
    }
  }
  
  // procedural generation
	DoMagic();

  // pathfinding
  UpdateAStarTiles();
}

void LevelGen::Load(const string& filename) {
	Unload();

	_currentMap = filename;
	string fullMapPath = "../Data/Media/Maps/" + filename;

  Serialiser serialiser;
  serialiser.Load(fullMapPath);
  Inflate(&serialiser);

  _world = WorldManager(this);
  
  GenerateEnemies();

  UpdateAStarTiles();
}

void LevelGen::Save(const string& filename) {
  Serialiser serialiser;
  Deflate(&serialiser);
 
  _currentMap = filename;
	string fullMapPath = "../Data/Media/Maps/" + filename;
  
  serialiser.Save(fullMapPath);
  
}

void LevelGen::Update(void) {
	_world.Update();
	// Update the map so we can render when camera moves.
}

void LevelGen::Render(void) {
	for(int i = 0; i < TILE_ARRAY_WIDTH; i++) {
		for(int j = 0; j < TILE_ARRAY_HEIGHT; j++) {
			_tile[i][j].Render();
		}
	}

	_world.Render();
}

void LevelGen::Unload(void) {
	_tileTextures.Unload();
	_entityTextures.Unload();
  for(int x = 0; x < TILE_ARRAY_WIDTH; x++) {
    for(int y = 0; y < TILE_ARRAY_HEIGHT; y++) {
      _tile[x][y] = MapTile();
    }
  }
}

void LevelGen::DoMagic(void) {
  GenerateEntities("tree", 45);
  GenerateEntities("bush", 30);
  GenerateEntities("hedge", 45);
  GenerateEntities("barrel", 50);
  GenerateEntities("barrel2", 100);
  GenerateEntities("stone", 55);
  GenerateEntities("stone2", 55);
  GenerateEntities("chest", 120); 
  GenerateEntities("chest2", 170); 
  GenerateEntities("chest3", 270);
  MakeWalkingPaths();
  GenerateEnemies();
}

void LevelGen::GenerateEntities(const string& name, int frequency) {
	int nextEntityGen = 1 + (rand() % frequency);
	std::string filename = "../Data/Media/Images/Entities/" + name + ".png";

	for(int x = 0; x < (TILE_ARRAY_WIDTH - 1); x++) {
		for(int y = 0; y < (TILE_ARRAY_HEIGHT - 1); y++) {
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

	for(int x = 0; x < TILE_ARRAY_WIDTH; x++) {
		bool pathFound = false;

		for(int y = 0; y < TILE_ARRAY_HEIGHT; y++) {
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
	xArg = rand() % ((TILE_ARRAY_WIDTH - 1) * TILE_WIDTH);
	yArg = rand() % ((TILE_ARRAY_HEIGHT - 1) * TILE_HEIGHT);
  
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
  
  for(int i = 0; i < TILE_ARRAY_WIDTH; i++) {
    for(int j = 0; j < TILE_ARRAY_HEIGHT; j++) {
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
  int npcsToGen = (_player->GetLevel() * 2) + (rand() % 4);
  
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
  
  float targetX = character->GetX() + xVel;
  float targetY = character->GetY() + yVel;
  
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
  
  for(int i = 0; i < TILE_ARRAY_WIDTH; i++) {
    for(int j = 0; j < TILE_ARRAY_HEIGHT; j++) {
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

bool LevelGen::AStarTilePassable(int xArg, int yArg) {
  SDL_Rect tileRect;
  tileRect.x = xArg * AStarTile::FAKE_SIZE;
  tileRect.y = yArg * AStarTile::FAKE_SIZE;
  tileRect.w = 40;
  tileRect.h = 45;

  for(int i = 0; i < TILE_ARRAY_WIDTH; i++) {
    for(int j = 0; j < TILE_ARRAY_HEIGHT; j++) {
      if(!_tile[i][j].GetEntitySolitity()) {
        continue;
      }
      
      SDL_Rect entityRect;
      entityRect.x = _tile[i][j].GetEntityX();
      entityRect.y = _tile[i][j].GetEntityY();
      entityRect.w = _tile[i][j].GetEntityWidth();
      entityRect.h = _tile[i][j].GetEntityHeight();
      
      if(CheckCollisionRect(tileRect, entityRect)) {
        return false;
      }
    }
  }

  SDL_Rect playerRect;
  playerRect.x = _player->GetX();
  playerRect.y = _player->GetY()/* + (_player->GetHeight() / 4) * 3*/;
  playerRect.w = _player->GetWidth();
  playerRect.h = _player->GetHeight()/* / 4*/;

  if(CheckCollisionRect(tileRect, playerRect)) {
    return false;
  }

  return true;
}

void LevelGen::UpdateAStarTiles(void) {
  for(int x = 0; x < ASTAR_ARRAY_WIDTH; x++) {
    for(int y = 0; y < ASTAR_ARRAY_HEIGHT; y++) {
      _astarTile[x][y] = AStarTile(this, x, y, AStarTilePassable(x, y));
    }
  }
}

void LevelGen::Deflate(Serialiser* serialiser) {
  serialiser->StepIn("map");
  for(int y = 0; y < TILE_ARRAY_HEIGHT; y++) {
    serialiser->StepIn("line");
    for(int x = 0; x < TILE_ARRAY_WIDTH; x++) {
      serialiser->StepIn("tile");
      _tile[x][y].Deflate(serialiser);
      serialiser->StepOut();
    }
    serialiser->StepOut();
  }
  serialiser->StepOut();
}

void LevelGen::Inflate(Serialiser* serialiser) {
  serialiser->FirstElement("map");
  
  x = 0;
  y = 0;

  while(serialiser->NextElement("line")) {
    x = 0;
    while(serialiser->NextElement("tile")) {
      _tile[x][y].Inflate(serialiser);
      x++;
    }
    serialiser->RollBack();
    y++;
  }

  for(x = 0; x < TILE_ARRAY_WIDTH; x++) {
    for(y = 0; y < TILE_ARRAY_HEIGHT; y++) {
      string tileTextureName = _tile[x][y].GetTileTextureName();
      if(tileTextureName != "null") {
        _tile[x][y].SetTileTexture(_tileTextures.AddAlpha("../Data/Media/Images/Tiles/" + tileTextureName + ".png"));
        _tile[x][y].SetTileXY(x * TILE_WIDTH, y * TILE_HEIGHT);
      }

			string entityTextureName = _tile[x][y].GetEntityTextureName();
      if(entityTextureName != "null") {
        _tile[x][y].SetEntityTexture(_entityTextures.AddAlpha("../Data/Media/Images/Entities/" + entityTextureName + ".png"));
        _tile[x][y].SetEntityXY(_tile[x][y].GetTileX() + TILE_WIDTH  / 2 - _tile[x][y].GetEntityWidth()  / 2,
                                _tile[x][y].GetTileY() + TILE_HEIGHT / 2 - _tile[x][y].GetEntityHeight() / 2);
      }

      
    }
  }
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

AStarTile& LevelGen::GetAStarTile(int xArg, int yArg) {
  return _astarTile[xArg][yArg];
}