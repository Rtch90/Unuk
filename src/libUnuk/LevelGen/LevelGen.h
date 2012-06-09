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
#include "../LevelGen/AStarTile.h"
#include "../System/Debug.h"
#include "../System/Serialisable.h"
#include "../Engine/WorldManager.h"
using namespace std;

class Character;
class Player;

class LevelGen : public Serialisable {
public:
  LevelGen(void);
  ~LevelGen(void);

  void New(void);
  void Load(const string& filename);
  void Save(const string& filename);
  void Update(void);
  void Render(void);

  void FindSpawnPoint(int& xArg, int& yArg, int objWidth, int objHeight);
  void MoveIfPossible(Character* character, float xVel, float yVel, bool isPlayer = false);

  bool GetTileSolidity(int xArg, int yArg);
  int  GetTileX(int xArg, int yArg);
  int  GetTileY(int xArg, int yArg);

  bool GetEntitySolidity(int xArg, int yArg);
  int  GetEntityX(int xArg, int yArg);
  int  GetEntityY(int xArg, int yArg);
  int  GetEntityWidth(int xArg, int yArg);
  int  GetEntityHeight(int xArg, int yArg);

  int  GetTileZLevel(int xArg, int yArg);

  AStarTile& GetAStarTile(int xArg, int yArg);

  string GetCurrentMap(void);

  WorldManager& GetWorld(void) { return _world; }

  void SetPlayer(Player* player)  { _player = player; }
  Player* GetPlayer()             { return _player; }

  static const int TILE_ARRAY_WIDTH = (SCREEN_WIDTH / TILE_WIDTH) + 1;
  static const int TILE_ARRAY_HEIGHT = (SCREEN_HEIGHT / TILE_HEIGHT) + 1;
  static const int ASTAR_ARRAY_WIDTH = TILE_ARRAY_WIDTH * (TILE_WIDTH / AStarTile::FAKE_SIZE);
  static const int ASTAR_ARRAY_HEIGHT = TILE_ARRAY_HEIGHT * (TILE_HEIGHT / AStarTile::FAKE_SIZE);

private:
  void Unload(void);
  void DoMagic(void);
  void GenerateEntities(const std::string& name, int frequency);
  void MakeWalkingPaths(void);
  void GenerateEnemies(void);
  bool AStarTilePassable(int xArg, int yArg);
  void UpdateAStarTiles(void);

  void Deflate(Serialiser* serialiser);
  void Inflate(Serialiser* serialiser);

  string _currentMap;
  int x;
  int y;

  MapTile _tile[TILE_ARRAY_WIDTH][TILE_ARRAY_HEIGHT];
  AStarTile _astarTile[ASTAR_ARRAY_WIDTH][ASTAR_ARRAY_HEIGHT];

  TextureManager _tileTextures;
  TextureManager _entityTextures;

  WorldManager _world;

  Player* _player;
};
