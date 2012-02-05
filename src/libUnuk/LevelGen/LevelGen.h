#pragma once
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <tinyxml.h>

#include "../../Unuk/Globals.h"
#include "../../Unuk/Constants.h"
#include "../Sprite/ImageLoader.h"
#include "../Sprite/ApplySurface.h"
#include "../LevelGen/MapTile.h"
#include "../System/Debug.h"
#include "../Engine/WorldManager.h"
using namespace std;

class Character;

class LevelGen {
public:
	LevelGen(void);
	~LevelGen(void);

  void Load(const string filename);
  void Update(void);
  void Render(void);
  
  void FindSpawnPoint(int& xArg, int& yArg, int objWidth, int objHeight);

	bool GetTileSolidity(int xArg, int yArg);
	int  GetTileX(int xArg, int yArg);
	int  GetTileY(int xArg, int yArg);

	bool GetEntitySolidity(int xArg, int yArg);
	int  GetEntityX(int xArg, int yArg);
	int  GetEntityY(int xArg, int yArg);
	int  GetEntityWidth(int xArg, int yArg);
	int  GetEntityHeight(int xArg, int yArg);

	int  GetTileZLevel(int xArg, int yArg);

	string GetCurrentMap(void);

	WorldManager& GetWorld(void) { return _world; }
  
  void MoveIfPossible(Character* character, float xVel, float yVel);

private:
  void Unload(void);
  void DoMagic(void);
  void GenerateEntities(const std::string& name, int frequency);
  void MakeWalkingPaths(void);
  void GenerateEnemies(void);

  string _currentMap;
  int x;
  int y;

  static const int TILE_ARRAY_SIZE = 150;
  MapTile _tile[TILE_ARRAY_SIZE][TILE_ARRAY_SIZE];
  
  static const int BOUNDARIES_X = (SCREEN_WIDTH / TILE_WIDTH) - 2;
  static const int BOUNDARIES_Y = (SCREEN_HEIGHT / TILE_HEIGHT) - 1;

  TextureManager _tileTextures;
  TextureManager _entityTextures;

  WorldManager _world;
};
