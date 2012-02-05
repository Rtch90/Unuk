#include "Character.h"

// Pixels * 60 / sec
const float Character::CHARACTER_SPEED = 3.5f;

static list<Character*>collisionList;
static list<Character*>::iterator collisionIter;

Character::Character(LevelGen* mapArg) {
  map = mapArg;
  attacking = false;
  directionFacing = FACING_DOWN;
  _animationStage  = ANIM_NO_FOOT;
  _animationTimer.Start();
  _leftFoot = false;
  _health = 100;

  xVel = 0.0f;
  yVel = 0.0f;
  
  _texture = NULL;
  
  collisionList.push_front(this);

  _healthBar.SetBackgroundRGB(0, 0, 0);
  _healthBar.SetForegroundRGB(255, 0, 0);

  _showHealthBar = false;
}

Character::~Character(void) {
  SDL_FreeSurface(_texture);
  for(collisionIter = collisionList.begin(); collisionIter != collisionList.end(); collisionIter++) {
    if((*collisionIter) == this) {
      collisionList.erase(collisionIter);
      break;
    }
  }
}

void Character::LoadSprites(string filename, int wArg, int hArg) {
  if(_texture != NULL)
    SDL_FreeSurface(_texture);

  _texture = LoadImageAlpha(filename.c_str());

  w = (float)wArg;
  h = (float)hArg;

  for(int m_direction = 0; m_direction < 4; m_direction++) {
    for(int m_action = 0; m_action < 4; m_action++) {
      _sprites[m_direction][m_action].x = (Sint16)(w * m_action);
      _sprites[m_direction][m_action].y = (Sint16)(h * m_direction);
      _sprites[m_direction][m_action].w = (Sint16)w;
      _sprites[m_direction][m_action].h = (Sint16)h;
    }
  }

  _healthBar.SetWidthHeight((int)w, 10);
}

void Character::Render(void) {
  if(attacking && attackTimer.GetTicks() < ATTACKING_DISPLAY_LEN) {
    ApplySurface((int)x, (int)y, _texture, screen, &_sprites[directionFacing][ANIM_ATTACK]);
    return;
  }
  else if(attacking)
    attacking = false;
  
  if(xVel == 0.0f && yVel == 0.0f)
    ApplySurface((int)x, (int)y, _texture, screen, &_sprites[directionFacing][ANIM_NO_FOOT]);
  else {
    if(_animationTimer.GetTicks() > ANIMATION_SPEED) {
      if(_animationStage == ANIM_NO_FOOT) {
        if(_leftFoot == true)
          _animationStage = ANIM_RIGHT_FOOT;
        else
          _animationStage = ANIM_LEFT_FOOT;
      }
      else if(_animationStage == ANIM_LEFT_FOOT) {
        _animationStage = ANIM_NO_FOOT;
        _leftFoot = true;
      }
      else if(_animationStage == ANIM_RIGHT_FOOT) {
        _animationStage = ANIM_NO_FOOT;
        _leftFoot = false;
      }
      _animationTimer.Start();
    }
    ApplySurface((int)x, (int)y, _texture, screen, &_sprites[directionFacing][_animationStage]);
  }

  if(_showHealthBar && (_healthBarDuration.GetTicks() >= 5000)) {
    _healthBarDuration.Stop();
    _showHealthBar = false;
  }

  if(_showHealthBar) {
    _healthBar.Draw();
  }
}

void Character::Update(void) {
  _healthBar.SetProgress((float)_health / 100.0f);
}

void Character::OnAttack(void) {
  _healthBarDuration.Start();
  _showHealthBar = true;
}

void Character::Move(void) {
  _healthBar.SetXY((int)x, (int)(y - _healthBar.GetHeight() - 5));
}
