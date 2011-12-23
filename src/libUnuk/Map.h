#ifndef _MAP_H_
#define _MAP_H_
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <tinyxml.h>

#include "../Unuk/Globals.h"
#include "../Unuk/Constants.h"
#include "ImageLoader.h"
#include "ApplySurface.h"
#include "MapTile.h"
#include "Debug.h"
using namespace std;

//class CharacterManager;

class Map {
public:
  Map(void);
  ~Map(void);

  void Load(const string filename);
  void Update(void);
  void Render(void);

  bool GetTileSolidity(int xArg, int yArg);
  int  GetTileX(int xArg, int yArg);
  int  GetTileY(int xArg, int yArg);

  bool GetEntitySolidity(int xArg, int yArg);
  int  GetEntityX(int xArg, int yArg);
  int  GetEntityY(int xArg, int yArg);
  int  GetEntityWidth(int xArg, int yArg);
  int  GetEntityHeight(int xArg, int yArg);

  int  GetTileZLevel(int xArg, int yArg);

  string GetMapTransitionName(int xArg, int yArg);
  int    GetMapTransitionX(int xArg, int yArg);
  int    GetMapTransitionY(int xArg, int yArg);

  string GetCurrentMap(void);

private:
  void Unload(void);

  string _currentMap;
  int x;
  int y;

  static const int TILE_ARRAY_SIZE = 150;
  MapTile _tile[TILE_ARRAY_SIZE][TILE_ARRAY_SIZE];

  TextureManager _tileTextures;
  TextureManager _entityTextures;
};

#endif
