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
	Vec2 realPos(x, y);
	Vec2 tilePos(tileX, tileY);

	if(realPos != tilePos) {
		float targetX = (float)(tileX * AStarTile::FAKE_SIZE);
		float targetY = (float)(tileY * AStarTile::FAKE_SIZE);

		float dx = targetX - realPos.x;
		float dy = targetY - realPos.y;

		float distance = sqrtf(dx*dx + dy*dy);

		if(fabs(distance) > CHARACTER_SPEED) {
			dx /= distance;
			dy /= distance;
			dx *= CHARACTER_SPEED;
			dy *= CHARACTER_SPEED;

			xVel = dx;
			yVel = dy;

			map->MoveIfPossible(this, xVel, yVel, false);

			Character::HealthBarScroll();

			_moving = true;
		} else {
			xVel = 0.0f;
			yVel = 0.0f;
			_moving = false;
		}
	} else {
		xVel = 0.0f;
		yVel = 0.0f;
		_moving = false;
	}

	if(_walkInPath && !_moving) {
		Vec2 targetPos((float)_target->GetX(), (float)_target->GetY());
		if(fabs(Vec2::Distance(targetPos, realPos)) <= CHARACTER_SPEED) {
			_target = _astar.GetSolutionNext();
			if(_target == NULL || _target == _lastTarget) {
				_walkInPath = false;
			} else {
				tileX = _target->GetX() / AStarTile::FAKE_SIZE;
				tileY = _target->GetY() / AStarTile::FAKE_SIZE;
			}
		}
	}
}

void NPC::OnPlayerMove(Player* player) {
	AStarTile& start = map->GetAStarTile(x / AStarTile::FAKE_SIZE, y / AStarTile::FAKE_SIZE);
	AStarTile& goal = map->GetAStarTile(player->GetX() / AStarTile::FAKE_SIZE, player->GetY() / AStarTile::FAKE_SIZE);

	_astar.SetStartAndGoalStates(start, goal);

	_walkInPath = false;

	// Dirty loop to calculate the path
	while(true) {
		unsigned int state = _astar.SearchStep();
		if(state == AStarSearch<AStarTile>::SEARCH_STATE_SUCCEEDED) {
			_walkInPath = true;
			break;
		} else if(state != AStarSearch<AStarTile>::SEARCH_STATE_SEARCHING) {
			break;
		}
	}

	_lastTarget = _astar.GetSolutionEnd();
	_target = _astar.GetSolutionStart();
	_target = _astar.GetSolutionNext();
	if(!_target) {
		_walkInPath = false;
	} else {
		tileX = _target->GetX() / AStarTile::FAKE_SIZE;
		tileY = _target->GetY() / AStarTile::FAKE_SIZE;
	}
}
