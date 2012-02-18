#pragma once

#include "Character.h"
#include "Pathfinding.h"
#include "../LevelGen/MapTile.h"

class Player;

class NPC : public Character {
public:
	NPC(LevelGen* mapArg);
	~NPC(void);

	void Update(void);

  void OnPlayerMove(Player* player);

protected:
	void Move(void);

private:
	int _moveChangeFrequency;

	int _moveDurationCurrent;
	int _moveDurationMin;
	int _moveDurationMax;

	bool _moving;

	Timer _moveTimer;

  AStarSearch<MapTile> _astar;
};
