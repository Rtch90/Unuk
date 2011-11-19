#ifndef _MAPTILE_H_
#define _MAPTILE_H_
#include <list>
#include <string>
using namespace std;

class MapTile {
public:
  MapTile(void)  {}
  ~MapTile(void) {}

  void SetTextureID(int arg)                        { m_textureID = arg; }
  int GetTextureID(void)                            { return m_textureID; }

  void SetTileSolidity(bool arg)                    { m_tileSolidity = arg; }
  bool GetTileSolidity(void)                        { return m_tileSolidity; }
  void SetTileXY(int xArg, int yArg)                { m_tileX = xArg, m_tileY = yArg; }
  int GetTileX(void)                                { return m_tileX; }
  int GetTileY(void)                                { return m_tileY; }

  void SetEntityID(int arg)                         { m_entityID = arg; }
  int GetEntityID(void)                             { return m_entityID; }

  void SetEntitySolidity(bool arg)                  { m_entityID = arg; }
  bool GetEntitySolitity(void)                      { return m_entitySolidity; }
  void SetEntityXY(int xArg, int yArg)              { m_entityX = xArg, m_entityY = yArg; }
  int GetEntityX(void)                              { return m_entityX; }
  int GetEntityY(void)                              { return m_entityY; }

  void SetEntityWidthHeight(int wArg, int hArg)     { m_entityW = wArg, m_entityH = hArg; }
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
  int m_textureID;
  bool m_tileSolidity;
  int m_tileX;
  int m_tileY;

  // Less than -1 if entity is present.
  int m_entityID;
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
