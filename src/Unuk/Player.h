#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL/SDL.h>

#include "Globals.h"
#include "Constants.h"
#include "../libUnuk/Character.h"

class Player : public Character {
public:
  Player(Map* mapArg);
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
};

#endif
