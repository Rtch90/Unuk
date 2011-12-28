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

  void Render(void)                                 { _tile.Render(), _entity.Render(); }

  // Tile Mutators.
  void SetTileTexture(SDL_Surface* arg)             { _tile.SetTexture(arg); }
  void SetTileSolidity(bool arg)                    { _tile.SetSolidity(arg); }
  bool GetTileSolidity(void)                        { return _tile.GetSolidity(); }
  // Well, it kinda helps if I lay the
  // tiles rather than just get the
  // return value right??
  void SetTileXY(int xArg, int yArg)                { _tile.SetXY(xArg, yArg); }
  int GetTileX(void)                                { return _tile.GetX(); }
  int GetTileY(void)                                { return _tile.GetY(); }

  // Entity Mutators.
  void SetEntityTexture(SDL_Surface* arg)           { _entity.SetTexture(arg); }
  void SetEntityXY(int xArg, int yArg)              { _entity.SetXY(xArg, yArg); }
  void SetEntitySolidity(bool arg)                  { _entity.SetSolidity(arg); }
  bool GetEntitySolitity(void)                      { return _entity.GetSolidity(); }

  // Entity Mutators.
  int GetEntityX(void)                              { return _entity.GetX(); }
  int GetEntityY(void)                              { return _entity.GetY(); }
  int GetEntityWidth(void)                          { return _entity.GetWidth(); }
  int GetEntityHeight(void)                         { return _entity.GetHeight(); }

  // ZLevel Mutators.
  void SetZLevel(int arg)                           { _zLevel = arg; }
  int GetZLevel(void)                               { return _zLevel; }

  // Map Transition Mutators.
  void SetMapTransitionName(string arg)             { _mapTransitionName = arg; }
  string GetMapTransitionName(void)                 { return _mapTransitionName; }

  void SetMapTransitionXY(int xArg, int yArg)       { _mapTransitionX = xArg, _mapTransitionY = yArg; }
  int GetMapTransitionX(void)                       { return _mapTransitionX; }
  int GetMapTransitionY(void)                       { return _mapTransitionY; }

private:
  MapElement _tile;
  MapEntityGeneric _entity;

  // -1 is a 'special' tile, the next tile that the player walks
  // on is the players new zlevel.
  int _zLevel;

  // If not 'null', switch map when the player walks on this tile.
  string _mapTransitionName;
  int _mapTransitionX;
  int _mapTransitionY;
};

#endif
