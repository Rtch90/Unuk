#include "AStarTile.h"
#include "../System/Vec2.h"
#include "../LevelGen/LevelGen.h"

bool AStarTile::IsSameState(AStarTile& tile) {
  return tile.x == x && tile.y == y;
}

bool AStarTile::IsGoal(AStarTile& tile) {
  return IsSameState(tile);
}

float AStarTile::GoalDistanceEstimate(AStarTile& goal) {
  Vec2 goalPos(goal.x * FAKE_SIZE, goal.y * FAKE_SIZE);
  Vec2 thisPos(x * FAKE_SIZE, y * FAKE_SIZE);
  return fabs(Vec2::DistanceSquared(thisPos, goalPos));
}

float AStarTile::GetCost(AStarTile& goal) {
  return FAKE_SIZE * FAKE_SIZE;
}

bool AStarTile::GetSuccessors(AStarSearch<AStarTile>* search) {
  if(_level->MetaTilePassable((x - 1) * FAKE_SIZE, y * FAKE_SIZE)) {
    AStarTile& successor = _level->GetAStarTile(x - 1, y);
    if(!search->AddSuccessor(successor)) {
      return false;
    }
  }

  if(_level->MetaTilePassable((x + 1) * FAKE_SIZE, y * FAKE_SIZE)) {
    AStarTile& successor = _level->GetAStarTile(x + 1, y);
    if(!search->AddSuccessor(successor)) {
      return false;
    }
  }

  if(_level->MetaTilePassable(x * FAKE_SIZE, (y - 1) * FAKE_SIZE)) {
    AStarTile& successor = _level->GetAStarTile(x, y - 1);
    if(!search->AddSuccessor(successor)) {
      return false;
    }
  }

  if(_level->MetaTilePassable(x * FAKE_SIZE, (y + 1) * FAKE_SIZE)) {
    AStarTile& successor = _level->GetAStarTile(x, y + 1);
    if(!search->AddSuccessor(successor)) {
      return false;
    }
  }

  return true;
}