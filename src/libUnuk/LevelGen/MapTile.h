#pragma once
#include <list>
#include <string>
#include <SDL/SDL.h>

#include "../../Unuk/Constants.h"
#include "../Sprite/ApplySurface.h"
#include "../LevelGen/MapElement.h"
#include "../LevelGen/MapEntities.h"
#include "../Engine/Pathfinding.h"
#include "../System/Vec2.h"
using namespace std;

class LevelGen;

class MapTile {
public:
	MapTile(LevelGen* level = NULL) : _level(level)   {  }
	~MapTile(void)                                    {  }

	void Render(void)                                 { _tile.Render(), _entity.Render(); }

	// Tile Mutators.
	SDL_Surface* SetTileTexture(SDL_Surface* arg)	 	  { _tile.SetTexture(arg); return NULL; }
	void         SetTileTextureName(string path)      { _tile.SetTextureName(path); }
	string       GetTileTextureName(void)             { return _tile.GetTextureName(); }
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
	void SetEntityTextureName(string path)            { _entity.SetTextureName(path); }
	void SetEntityXY(int xArg, int yArg)              { _entity.SetXY(xArg, yArg); }
	void SetEntitySolidity(bool arg)                  { _entity.SetSolidity(arg); }
	bool GetEntitySolitity(void)                      { return _entity.GetSolidity(); }

	// Entity Mutators.
	int GetEntityX(void)                              { return _entity.GetX(); }
	int GetEntityY(void)                              { return _entity.GetY(); }
	int GetEntityWidth(void)                          { return _entity.GetWidth(); }
	int GetEntityHeight(void)                         { return _entity.GetHeight(); }
	string GetEntityTextureName(void)                 { return _entity.GetTextureName(); }

	// ZLevel Mutators.
	void SetZLevel(int arg)                           { _zLevel = arg; }
	int GetZLevel(void)                               { return _zLevel; }

	// Pathfinding stuff.
	MapTile(const MapTile& source);
	bool IsSameState(MapTile& tile);
	bool IsGoal(MapTile& tile);
	float GoalDistanceEstimate(MapTile& goal);
	float GetCost(MapTile& goal);
	bool GetSuccessors(AStarSearch<MapTile>* search, MapTile* parent);

private:
	LevelGen* _level;
	MapElement _tile;
	MapEntityGeneric _entity;

	// -1 is a 'special' tile, the next tile that the player walks
	// on is the players new zlevel.
	int _zLevel;
};
