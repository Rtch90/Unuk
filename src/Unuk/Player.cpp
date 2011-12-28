#include "Player.h"

// Pixels * 60 / sec.
const float Player::PLAYER_SPEED = Character::CHARACTER_SPEED + 0.5;

Player::Player(Map *mapArg) : Character(mapArg) {

}

Player::~Player(void) {

}

void Player::HandleInput(void) {
  if(event.key.type == SDL_KEYDOWN) {
    switch(event.key.keysym.sym) {
    case SDLK_w:
      yVel -= PLAYER_SPEED;
      xVel = 0;
      directionFacing = FACING_UP;
      break;
    case SDLK_s:
      yVel += PLAYER_SPEED;
      xVel = 0;
      directionFacing = FACING_DOWN;
      break;
    case SDLK_a:
      xVel -= PLAYER_SPEED;
      yVel = 0;
      directionFacing = FACING_LEFT;
      break;
    case SDLK_d:
      xVel += PLAYER_SPEED;
      yVel = 0;
      directionFacing = FACING_RIGHT;
      break;
    default:
      break;
    }
  }
  else if(event.key.type == SDL_KEYUP) {
    switch(event.key.keysym.sym) {
    case SDLK_w: yVel = 0; break;
    case SDLK_s: yVel = 0; break;
    case SDLK_a: xVel = 0; break;
    case SDLK_d: xVel = 0; break;
    default: break;
    }
  }
  else if(event.type == SDL_MOUSEBUTTONDOWN) {
    if(event.button.button == SDL_BUTTON_LEFT) {
      attacking = true;
      attackTimer.Start();
    }
  }
}

void Player::Update(void) {
  Move();
  AddSpeachBubble("Woot, My name is Allanis, welcome to my home");

  // For now The camera will be static.
  SetCamera();
}

void Player::SetName(string nameArg) {
  _name = nameArg;
}

void Player::SetCamera(void) {
  camera.x = (x + w / 2) - SCREEN_WIDTH  / 2;
  camera.y = (y + h / 2) - SCREEN_HEIGHT / 2;

  if(camera.x < 0)
    camera.x = 0;
  if(camera.y < 0)
    camera.y = 0;

  if(camera.x > levelWidth - camera.w)
    camera.x = levelWidth - camera.w;
  if(camera.y > levelHeight - camera.h)
    camera.y = levelHeight = camera.h;
}

void Player::Move() {
  Character::Move();
  if(map->GetMapTransitionName(tileX, tileY) != "null") {
    SetXY(map->GetMapTransitionX(tileX, tileY), map->GetMapTransitionY(tileX, tileY));
    map->Load(map->GetMapTransitionName(tileX, tileY));
  }
}
