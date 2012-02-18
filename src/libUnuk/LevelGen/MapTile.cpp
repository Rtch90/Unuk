#include "MapTile.h"
#include "LevelGen.h"

MapTile::MapTile(const MapTile& source) {
	_level = source._level;
	_tile = source._tile;
	_entity = source._entity;
	_zLevel = source._zLevel;
}

bool MapTile::IsSameState(MapTile& tile) {
	return (tile.GetTileX() == _tile.GetX()) && (tile.GetTileY() == _tile.GetY());
}

bool MapTile::IsGoal(MapTile& tile) {
	return IsSameState(tile);
}

float MapTile::GoalDistanceEstimate(MapTile& goal) {
	Vec2 thisPos(_tile.GetX(), _tile.GetY());
	Vec2 goalPos(goal.GetTileX(), goal.GetTileY());
	return fabs(Vec2::DistanceSquared(thisPos, goalPos));
}

float MapTile::GetCost(MapTile& goal) {
	return 64.0f*64.0f;
}

bool MapTile::GetSuccessors(AStarSearch<MapTile>* search, MapTile* parent) {
	int tileX = _tile.GetX() / TILE_WIDTH;
	int tileY = _tile.GetY() / TILE_HEIGHT;

	// Add tile to the left if possible.
	if(tileX > 0) {
		MapTile& successor = _level->GetTile(tileX - 1, tileY);
		if(successor.GetTileSolidity() || successor.GetEntitySolitity()) {
			search->AddSuccessor(successor);
		}
	}

	// Add tile to the right if possible
	// TODO: replace 64 with map width
	if(tileX < 64) {
		MapTile& successor = _level->GetTile(tileX + 1, tileY);
		if(successor.GetTileSolidity() || successor.GetEntitySolitity()) {
			search->AddSuccessor(successor);
		}
	}

	// Add tile to the bottom if possible
	if(tileY > 0) {
		MapTile& successor = _level->GetTile(tileX, tileY - 1);
		if(successor.GetTileSolidity() || successor.GetEntitySolitity()) {
			search->AddSuccessor(successor);
		}
	}

	// Add tile to the top if possible
	// TODO: replace 64 with map height
	if(tileY < 64) {
		MapTile& successor = _level->GetTile(tileX, tileY + 1);
		if(successor.GetTileSolidity() || successor.GetEntitySolitity()) {
			search->AddSuccessor(successor);
		}
	}

	return true;
}
