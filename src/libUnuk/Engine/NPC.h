#pragma once

#include "Character.h"
#include "Pathfinding.h"
#include "../LevelGen/AStarTile.h"
#include "../System/Timer.h"

class Player;

class NPC : public Character {
public:
  NPC(LevelGen* mapArg);
  ~NPC(void);

  void ForceMove(void);
  void Update(void);

  void OnPlayerMove(Player* player);

protected:
  void Move(void);
  void AttackPlayer(void);

private:
  bool _moving;

  AStarSearch<AStarTile> _astar;
  bool _walkInPath;
  AStarTile* _target;
  AStarTile* _lastTarget;

  Timer _attackTimer;

  static const int ATTACK_FREQUENCY = 1000;
};
