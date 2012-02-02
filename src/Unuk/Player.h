#pragma once
#include <SDL/SDL.h>

#include "Globals.h"
#include "Constants.h"
#include "../libUnuk/Engine/Character.h"
#include "../libUnuk//System/Debug.h"

class Player : public Character {
public:
  Player(LevelGen* mapArg);
  ~Player(void);

  void HandleInput(void);
  void Update(void);

  void SetName(string nameArg);
  string GetName(void) { return _name; }
  
  void SetLevel(int level);
  int GetLevel(void) { return _level; }

  void SetExp(int exp);
  int GetExp(void) { return _exp; }
  
  void SetLevelLiteral(int level) { _level = level; }
  void SetExpLiteral(int exp) { _exp = exp; }
  void SetHealthLiteral(int health) { _health = health; }
  
  static const int MAX_LEVEL = 10;
  static const int EXP_TABLE[MAX_LEVEL];
  
protected:
  void Move(void);
  void CheckTileCollisions(void);

private:
  void SetCamera(void);
  static const float PLAYER_SPEED;

  string _name;
  int _level;
  int _exp;
};
