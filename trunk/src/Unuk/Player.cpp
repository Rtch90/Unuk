#include <GL/gl.h>
#include <SDL/SDL.h>
#include "../libUnuk/Sprite.h"
#include "../libUnuk/Debug.h"
#include "Player.h"

Player::Player(void) {
  m_posx = 0;
  m_posy = 0;
}

Player::~Player(void) {
  CleanUp();
}

void Player::Prepare(void) {
  m_player = new Sprite("../Data/Media/test.bmp");
  // I borked up the image loader, so for now we will
  // rotate the image 180 degrees.
  m_player->Rotate(180);
  // Set our pivot to the top right.
  m_player->SetPivot(1.0f, 1.0f);

  if(m_velx && m_vely > 0) {
    m_posx += m_velx;
    m_posy += m_vely;
  }
  SetPosition(m_posx, m_posy);
}

void Player::Render(void) {
  // Only render calls should appear here.
  m_player->Render();
}

void Player::SetPosition(GLdouble posx, GLdouble posy) {
  // -- Set the position of the player sprite.
  m_posx = posx;
  m_posy = posy;

  m_player->SetX(m_posx);
  m_player->SetY(m_posy);
}

void Player::SetVelocity(GLdouble velx, GLdouble vely) {
  m_velx = velx;
  m_vely = vely;
}

void Player::CleanUp(void) {
  delete m_player;
}
