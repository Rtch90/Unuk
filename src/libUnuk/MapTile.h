#ifndef _MAPTILE_H_
#define _MAPTILE_H_
#include <list>
#include <string>
#include <SDL/SDL.h>

#include "Entity.h"
using namespace std;

class MapTile {
public:
  MapTile(void)  {}
  ~MapTile(void) {}

  void SetTileTexture(SDL_Surface* surface)         { m_tileTexture = surface; }
  SDL_Surface* GetTileTexture(void)                 { return m_tileTexture; }

  void SetTileSolidity(bool arg)                    { m_tileSolidity = arg; }
  bool GetTileSolidity(void)                        { return m_tileSolidity; }
  void SetTileXY(int xArg, int yArg)                { m_tileX = xArg, m_tileY = yArg; }
  int GetTileX(void)                                { return m_tileX; }
  int GetTileY(void)                                { return m_tileY; }

  void SetEntityTexture(SDL_Surface* surface) {
    m_entityTexture = surface;
    if(m_entityTexture != NULL) {
      m_entityW = m_entityTexture->w;
      m_entityH = m_entityTexture->h;
    }
  }
  SDL_Surface* GetEntityTexture(void)               { return m_entityTexture; }
  void SetEntitySolidity(bool arg)                  { m_entitySolidity = arg; }
  bool GetEntitySolitity(void)                      { return m_entitySolidity; }
  void SetEntityXY(int xArg, int yArg)              { m_entityX = xArg, m_entityY = yArg; }
  int GetEntityX(void)                              { return m_entityX; }
  int GetEntityY(void)                              { return m_entityY; }

  int GetEntityWidth(void)                          { return m_entityW; }
  int GetEntityHeight(void)                         { return m_entityH; }

  void SetZLevel(int arg)                           { m_zLevel = arg; }
  int GetZLevel(void)                               { return m_zLevel; }

  void SetMapTransitionName(string arg)             { m_mapTransitionName = arg; }
  string GetMapTransitionName(void)                 { return m_mapTransitionName; }

  void SetMapTransitionXY(int xArg, int yArg)       { m_mapTransitionX = xArg, m_mapTransitionY = yArg; }
  int GetMapTransitionX(void)                       { return m_mapTransitionX; }
  int GetMapTransitionY(void)                       { return m_mapTransitionY; }

private:
  SDL_Surface* m_entityTexture;
  bool m_tileSolidity;
  int m_tileX;
  int m_tileY;

  SDL_Surface* m_tileTexture;
  bool m_entitySolidity;
  int m_entityX;
  int m_entityY;
  int m_entityW;
  int m_entityH;

  // -1 is a 'special' tile, the next tile that the player walks
  // on is the new player z-level.
  int m_zLevel;

  //If not 'n', switch map when the player walks on this tile.
  string m_mapTransitionName;
  int m_mapTransitionX;
  int m_mapTransitionY;
};

#endif
