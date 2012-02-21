#include "NPC.h"
#include "../../Unuk/Player.h"
#include "../System/Vec2.h"

NPC::NPC(LevelGen* mapArg) : Character(mapArg) {
	_walkInPath = false;
	_moving = false;
}

NPC::~NPC(void) {

}

void NPC::ForceMove(void) {
	tileX = x / AStarTile::FAKE_SIZE;
	tileY = y / AStarTile::FAKE_SIZE;
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
  Character::HealthBarScroll();
  
  xVel = 0.0f;
  yVel = 0.0f;
  
  if(!_walkInPath) {
    return;
  }
  
	Vec2 realPos(x, y);
  
  Character* player = map->GetPlayer();
  
  if(fabs((player->GetX() - x)) > 256 || fabs((player->GetY() - y)) > 256) {
    return;
  }
  
  SDL_Rect selfRect;
  selfRect.x = x - 5;
  selfRect.y = y - 5;
  selfRect.w = w + 5;
  selfRect.h = h + 5;
  
  SDL_Rect playerRect;
  playerRect.x = player->GetX() - 5;
  playerRect.y = player->GetY() - 5;
  playerRect.w = player->GetWidth() + 5;
  playerRect.h = player->GetHeight() + 5;
  
  if(CheckCollisionRect(selfRect, playerRect)) {
    _walkInPath = false;
    return;
  }
  
  float targetX = (float)(tileX * AStarTile::FAKE_SIZE);
  float targetY = (float)(tileY * AStarTile::FAKE_SIZE);

  float dx = targetX - realPos.x;
  float dy = targetY - realPos.y;
  
  if(dx > 0.0f) {
    xVel = CHARACTER_SPEED;
  }
  else if(dx < 0.0f) {
    xVel = -CHARACTER_SPEED;
  }
 if(dy > 0.0f) {
    yVel = CHARACTER_SPEED;
  }
  else if(dy < 0.0f) {
    yVel = -CHARACTER_SPEED;
  } 
 
  if(xVel != 0.0f || yVel != 0.0f) { 
    map->MoveIfPossible(this, xVel, yVel, false);
  }
  else {
    _target = _astar.GetSolutionNext();
    
    if(_target == NULL || _target == _lastTarget) {
      _walkInPath = false;
    } else {
      tileX = _target->GetX() / AStarTile::FAKE_SIZE;
      tileY = _target->GetY() / AStarTile::FAKE_SIZE;
    }
  }
}

void NPC::OnPlayerMove(Player* player) {
  if(fabs((player->GetX() - x)) > 256 || fabs((player->GetY() - y)) > 256) {
    return;
  }
  
	AStarTile& start = map->GetAStarTile(x / AStarTile::FAKE_SIZE, y / AStarTile::FAKE_SIZE);
	AStarTile& goal = map->GetAStarTile(player->GetX() / AStarTile::FAKE_SIZE, player->GetY() / AStarTile::FAKE_SIZE);

	_astar.SetStartAndGoalStates(start, goal);

	_walkInPath = false;

	while(true) {
		unsigned int state = _astar.SearchStep();
		if(state == AStarSearch<AStarTile>::SEARCH_STATE_SUCCEEDED) {
			_walkInPath = true;
			break;
		} else if(state != AStarSearch<AStarTile>::SEARCH_STATE_SEARCHING) {
			break;
		}
	}

  if(_walkInPath) {
    _lastTarget = _astar.GetSolutionEnd();
    
    _target = _astar.GetSolutionStart();
    _target = _astar.GetSolutionNext();
    
    if(_target == NULL) {
      _walkInPath = false;
      _target = NULL;
    } else {
      tileX = _target->GetX() / AStarTile::FAKE_SIZE;
      tileY = _target->GetY() / AStarTile::FAKE_SIZE;
    }
  }
}
