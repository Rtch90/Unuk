#ifndef _MAPTILE_H_
#define _MAPTILE_H_
#include <list>
#include <string>
#include <SDL/SDL.h>

#include "../Unuk/Constants.h"
#include "ApplySurface.h"
#include "MapElement.h"
#include "MapEntities.h"
using namespace std;

class MapTile {
public:
  MapTile(void)                                     {  }
  ~MapTile(void)                                    {  }

  void Render(void)                                 { m_tile.Render(), m_entity.Render(); }

  // Tile Mutators.
  SDL_Surface SetTileTexture(SDL_Surface* arg)      { m_tile.SetTexture(arg); }
  void SetTileSolidity(bool arg)                    { m_tile.SetSolidity(arg); }
  bool GetTileSolidity(void)                        { return m_tile.GetSolidity(); }
  void SetTileXY(int xArg, int yArg)                { m_tile.GetX(), m_tile.GetY(); }
  int GetTileX(void)                                { return m_tile.GetX(); }
  int GetTileY(void)                                { return m_tile.GetY(); }

  // Entity Mutators.
  void SetEntityTexture(SDL_Surface* arg)           { m_entity.SetTexture(arg); }
  void SetEntityXY(int xArg, int yArg)              { m_entity.SetXY(xArg, yArg); }
  void SetEntitySolidity(bool arg)                  { m_entity.SetSolidity(arg); }
  bool GetEntitySolitity(void)                      { return m_entity.GetSolidity(); }

  // Entity Mutators.
  int GetEntityX(void)                              { return m_entity.GetX(); }
  int GetEntityY(void)                              { return m_entity.GetY(); }
  int GetEntityWidth(void)                          { return m_entity.GetWidth(); }
  int GetEntityHeight(void)                         { return m_entity.GetHeight(); }

  // ZLevel Mutators.
  void SetZLevel(int arg)                           { m_zLevel = arg; }
  int GetZLevel(void)                               { return m_zLevel; }

  // Map Transition Mutators.
  void SetMapTransitionName(string arg)             { m_mapTransitionName = arg; }
  string GetMapTransitionName(void)                 { return m_mapTransitionName; }

  void SetMapTransitionXY(int xArg, int yArg)       { m_mapTransitionX = xArg, m_mapTransitionY = yArg; }
  int GetMapTransitionX(void)                       { return m_mapTransitionX; }
  int GetMapTransitionY(void)                       { return m_mapTransitionY; }

private:
  MapElement m_tile;
  MapEntityGeneric m_entity;

  // -1 is a 'special' tile, the next tile that the player walks
  // on is the players new zlevel.
  int m_zLevel;

  // If not 'null', switch map when the player walks on this tile.
  string m_mapTransitionName;
  int m_mapTransitionX;
  int m_mapTransitionY;
};

#endif
