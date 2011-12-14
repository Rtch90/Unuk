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
#include "TextureManager.h"
#include "MapTile.h"
#include "Debug.h"
using namespace std;

//class CharacterManager;

class Map {
public:
  Map(void);
  ~Map(void);

  void Load(const string filename);
  void Render(void);

  bool GetTileSolidity(int row, int column);
  int  GetTileX(int row, int column);
  int  GetTileY(int row, int column);

  bool GetEntitySolidity(int row, int column);
  int  GetEntityX(int row, int column);
  int  GetEntityY(int row, int column);
  int  GetEntityWidth(int row, int column);
  int  GetEntityHeight(int row, int column);

  int  GetTileZLevel(int row, int column);

  string GetMapTransitionName(int row, int column);
  int    GetMapTransitionX(int row, int column);
  int    GetMapTransitionY(int row, int column);

  string GetCurrentMap(void);

private:
  void Unload(void);

  string m_currentMap;
  int x;
  int y;

  TextureManager m_tileTextures;
  TextureManager m_entityTextures;

  static const int TILE_ARRAY_SIZE = 150;
  MapTile m_tile[TILE_ARRAY_SIZE][TILE_ARRAY_SIZE];
};

#endif
