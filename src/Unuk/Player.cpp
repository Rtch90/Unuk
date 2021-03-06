#include "Player.h"
#include "Globals.h"
#include "../libUnuk/UI/EventHistory.h"
#include "../libUnuk/System/Input.h"

// Pixels * 60 / sec.
const float Player::PLAYER_SPEED = Character::CHARACTER_SPEED + 1.0f;

// Amount of Exp needed every level
const int Player::EXP_TABLE[MAX_LEVEL] = {
  10,
  30,
  90,
  150,
  300,
  512,
  1000,
  2000,
  3500,
  5000,
  6500,
  8500,
  10250,
  12000,
  15000,
  25000,
  50000,
  65000,
  80000,
  100000
};

Player::Player(LevelGen *mapArg) : Character(mapArg) {
  _level = 1;
  _exp = 0;
  _lastTileX = 0;
  _lastTileY = 0;
}

Player::~Player(void) {

}

void Player::HandleInput(void) {
  if(event.key.type == SDL_KEYDOWN) {
    switch(event.key.keysym.sym) {
    case SDLK_w:
    case SDLK_UP:
      yVel -= PLAYER_SPEED;
      xVel = 0;
      directionFacing = FACING_UP;
      break;
    case SDLK_s:
    case SDLK_DOWN:
      yVel += PLAYER_SPEED;
      xVel = 0;
      directionFacing = FACING_DOWN;
      break;
    case SDLK_a:
    case SDLK_LEFT:
      xVel -= PLAYER_SPEED;
      yVel = 0;
      directionFacing = FACING_LEFT;
      break;
    case SDLK_d:
    case SDLK_RIGHT:
      xVel += PLAYER_SPEED;
      yVel = 0;
      directionFacing = FACING_RIGHT;
      break;
    case SDLK_SPACE:
      attacking = true;
      attackTimer.Start();
      map->GetWorld().OnPlayerAttack(this);
      break;
    default:
      break;
    }
  }
  else if(event.key.type == SDL_KEYUP) {
    switch(event.key.keysym.sym) {
    case SDLK_w: case SDLK_UP:      yVel = 0; break;
    case SDLK_s: case SDLK_DOWN:    yVel = 0; break;
    case SDLK_a: case SDLK_LEFT:    xVel = 0; break;
    case SDLK_d: case SDLK_RIGHT:   xVel = 0; break;
    default: break;
    }
  }
  else if(event.type == SDL_MOUSEBUTTONDOWN) {
    if(event.button.button == SDL_BUTTON_LEFT) {
      attacking = true;
      attackTimer.Start();
      map->GetWorld().OnPlayerAttack(this);
    }
  }
}

void Player::Update(void) {
  Move();
  //AddSpeachBubble("Woot, My name is Allanis, welcome to my home. Just testing some more text to see if this works..");

  // For now The camera will be static.
  //SetCamera();

  tileX = x / AStarTile::FAKE_SIZE;
  tileY = y / AStarTile::FAKE_SIZE;

  if(tileX != _lastTileX || tileY != _lastTileY) {
    _lastTileX = tileX;
    _lastTileY = tileY;

    map->GetWorld().OnPlayerMove(this);
  }

  _healthBar.SetProgress((float)GetHealth() / 100.0f);
}

void Player::SetName(string nameArg) {
  _name = nameArg;
}

void Player::Move() {
  map->MoveIfPossible(this, xVel, yVel, true);
  Character::HealthBarScroll();
}

void Player::SetLevel(int level) {
  _level = level;
  _exp = _exp - EXP_TABLE[level - 1];
  if(_exp < 0) {
    _exp = 0;
  }
  if(_level == MAX_LEVEL) {
    eventHistory->LogEvent("YOU BEAT IT! I'M SO PROUD!");
    eventHistory->LogEvent("*Sheds Tear*");
  }
}

void Player::SetExp(int exp) {
  std::stringstream evtMsg;
  evtMsg << "Gained " << (exp - _exp) << " Experience Points.";
  eventHistory->LogEvent(evtMsg.str());

  _exp = exp;
  if(_level != MAX_LEVEL && _exp >= EXP_TABLE[_level - 1]) {
    eventHistory->LogEvent("Player leveled up!");
    SetLevel(_level + 1);
  }
}
