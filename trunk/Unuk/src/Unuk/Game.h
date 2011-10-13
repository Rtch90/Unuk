#ifndef _GAME_H_
#define _GAME_H_
#include "Player.h"

class Game {
public:
  Game(void);
  ~Game(void);

  bool Init(void);
  void Prepare(float dt);
  void Render(void);
  void Shutdown(void);

  void UpdateProjection();
  void OnResize(int width, int height);

private:
  float m_rotationAngle;
  Player *m_player;
};

#endif 
