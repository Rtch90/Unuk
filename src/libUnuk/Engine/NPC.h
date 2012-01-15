#pragma once

#include "Character.h"
#include "AStar.h"

class NPC : public Character {
public:
  NPC(LevelGen* mapArg);
  ~NPC(void);
  
  void Update(void);

protected:
  void Move(void);
  
private:
  int _moveChangeFrequency;
  
  int _moveDurationCurrent;
  int _moveDurationMin;
  int _moveDurationMax;
  
  bool _moving;
  
  Timer _moveTimer;
};
