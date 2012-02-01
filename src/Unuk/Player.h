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
  
  void SetExpNeeded(int expNeeded);
  int GetExpNeeded(void) { return _expNeeded; }
  
  static const int BASE_EXP_NEEDED;
  
protected:
  void Move(void);
  void CheckTileCollisions(void);

private:
  void SetCamera(void);
  static const float PLAYER_SPEED;

  string _name;
  //int _health;
  int _level;
  int _exp;
  int _expNeeded;
};
