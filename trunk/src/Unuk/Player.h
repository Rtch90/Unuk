#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL/SDL.h>
#include "../libUnuk/Sprite.h"

class Player {
public:
  Player(void);
  ~Player(void);

  void Prepare(void);
  void Render(void);

  void SetPosition(GLdouble posx, GLdouble posy);
  void SetVelocity(GLdouble velx, GLdouble vely);

  void CleanUp(void);
  
private:
  Sprite *m_player;

  // Position variables.
  GLdouble m_tempx;
  GLdouble m_tempy;
  GLdouble m_posx;
  GLdouble m_posy;

  // Velocity variables.
  int m_tempvelx;
  int m_tempvely;
  int m_velx;
  int m_vely;
};

#endif
