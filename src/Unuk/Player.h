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

protected:
  void Move(void);
  void CheckTileCollisions(void);

private:
  void SetCamera(void);
  static const float PLAYER_SPEED;

  string _name;
  //int _health;
};
