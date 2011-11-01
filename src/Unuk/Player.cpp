#include <GL/gl.h>
#include <SDL/SDL.h>
#include "../libUnuk/Sprite.h"
#include "../libUnuk/Debug.h"
#include "../libUnuk/Input.h"
#include "Player.h"

Player::Player(void) : m_posx(0), m_posy(0) {
  //m_player = new Sprite("../Data/Media/test.bmp");
}

Player::~Player(void) {
  CleanUp();
}

void Player::Prepare(void) {
  // I borked up the image loader, so for now we will
  // rotate the image 180 degrees.
  m_player->Rotate(180);
  m_player->SetScale(0.5f, 0.5f);
  //Set our pivot to the top right.
  m_player->SetPivot(1.0f, 1.0f);

  CreateInput();
  // Move the player.
  if(KeyStillDown(SDLK_w) || KeyStillDown(SDLK_UP))     { SetVelocity(0, -5); }
  if(KeyStillDown(SDLK_a) || KeyStillDown(SDLK_LEFT))   { SetVelocity(-5, 0); }
  if(KeyStillDown(SDLK_s) || KeyStillDown(SDLK_DOWN))   { SetVelocity( 0, 5); }
  if(KeyStillDown(SDLK_d) || KeyStillDown(SDLK_RIGHT))  { SetVelocity( 5, 0); }
  UpdateInput();

  SetPosition(m_posx, m_posy);  
}

void Player::Render(void) {
  // Only render calls should appear here.
  m_player->Render();
}

void Player::SetSprite(void) {
  m_player = new Sprite("../Data/Media/test.bmp");
}

void Player::SetPosition(GLdouble posx, GLdouble posy) {
  // Set the position of the player sprite.
  m_posx = posx;
  m_posy = posy;

  m_player->SetX(m_posx);
  m_player->SetY(m_posy);
}

void Player::SetVelocity(GLdouble velx, GLdouble vely) {
  m_velx = velx;
  m_vely = vely;

  m_posx += m_velx;
  m_posy += m_vely;
}

void Player::CleanUp(void) {
  delete m_player;
}
