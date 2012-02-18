#include "NPC.h"
#include "../Unuk/Player.h"

NPC::NPC(LevelGen* mapArg) : Character(mapArg) {
  _moveTimer.Start();
  
  _moveChangeFrequency = 14000;
  _moveDurationMax	= 3000;
  _moveDurationMin	= 1000;
}

NPC::~NPC(void) {

}

void NPC::Update(void) {
  // Store the NPC's health.
  // int health = GetHealth(); // not referenced

  Move();

  if(xVel > 0) directionFacing          = FACING_RIGHT;
  else if(xVel < 0) directionFacing     = FACING_LEFT;
  else if(yVel > 0) directionFacing     = FACING_DOWN;
  else if(yVel < 0) directionFacing     = FACING_UP;

  _healthBar.SetProgress((float)GetHealth() / 100.0f);
}

void NPC::Move(void) {
  if(_moving && _moveTimer.GetTicks() > _moveDurationMax) {
    xVel = 0.0f;
    yVel = 0.0f;
    _moving = false;
  }
  
  if(_moving && _moveTimer.GetTicks() >= _moveDurationCurrent) {
    xVel = 0.0f;
    yVel = 0.0f;
    _moving = false;
  }
  
  if(_moveTimer.GetTicks() > _moveChangeFrequency) {
    _moveTimer.Start();
    _moveDurationCurrent = _moveDurationMin + (rand() % (_moveDurationMax - _moveDurationMin));
    if(rand() % 2) {
      yVel = 0.0f;
      if(rand() % 2)
        xVel = CHARACTER_SPEED;
      else
        xVel = -CHARACTER_SPEED;
    } else {
      xVel = 0.0f;
      if(rand() % 2)
        yVel = CHARACTER_SPEED;
      else
        yVel = -CHARACTER_SPEED;
    }
    _moving = true;
  }
  
  map->MoveIfPossible(this, xVel, yVel, false);
  Character::HealthBarScroll();
}

void NPC::OnPlayerMove(Player* player) {
  MapTile& start = map->GetTile(x / TILE_WIDTH, y / TILE_HEIGHT);
  MapTile& goal = map->GetTile(player->GetX() / TILE_WIDTH, player->GetY() / TILE_HEIGHT);

  _astar.SetStartAndGoalStates(start, goal);

  bool solutionFound = false;

  // Dirty loop to calculate the path
  while(true) {
    _astar.SearchStep();

    int state = _astar.GetState();
    if(state == AStarSearch<MapTile>::SEARCH_STATE_SUCCEEDED) {
      solutionFound = true;
      break;
    } else if(state == AStarSearch<MapTile>::SEARCH_STATE_SEARCHING) {
      continue;
    } else {
      break;
    }
  }

  if(solutionFound) {
    x = _astar.GetSolutionEnd()->GetTileX();
    y = _astar.GetSolutionEnd()->GetTileY();
  }
}
