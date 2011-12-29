#include "Character.h"

// Pixels * 60 / sec
const float Character::CHARACTER_SPEED = 3.5f;

static list<Character*>collisionList;
static list<Character*>::iterator collisionIter;

Character::Character(Map* mapArg) {
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

  w = wArg;
  h = hArg;

  for(int m_direction = 0; m_direction < 4; m_direction++) {
    for(int m_action = 0; m_action < 4; m_action++) {
      _sprites[m_direction][m_action].x = w * m_action;
      _sprites[m_direction][m_action].y = h * m_direction;
      _sprites[m_direction][m_action].w = w;
      _sprites[m_direction][m_action].h = h;
    }
  }
}

void Character::AddSpeachBubble(string text) {
  _speachBubble.push_back(text);

  _speachBubbleText.SetTextBlended(text, small, 0, 0, 0);

  if(_speachBubbleTimer.IsStarted() == false)
    _speachBubbleTimer.Start();
}

void Character::Render(void) {
  // Draw some fancy speach bubbles. It is a bit of a mess, I am playing.
  if(_speachBubble.size() != 0) {
    if(_speachBubbleTimer.GetTicks() < SPEACH_BUBBLE_DISPLAY_LENGTH) {
      roundedBoxRGBA(screen, (x + w / 2) - 100 - camera.x,
                     y - 100 - camera.y,
                     (x + w / 2) + 100 - camera.x,
                     y - 35 - camera.y,
                     5, 255, 255, 255, 255);

      filledTrigonRGBA(screen, (x + w / 2) - 100 - camera.x,
                       y - 100 - camera.y,
                       (x + w / 2) - 10 - camera.x,
                       y - 40 - camera.y,
                       (x + w / 2) + 10 - camera.x,
                       y - 40 - camera.y,
                       255, 255, 255, 255);

      _speachBubbleText.Render((x + w / 2) - 90, y - 90);
    }
  }

  if(attacking && attackTimer.GetTicks() < ATTACKING_DISPLAY_LEN) {
    ApplySurface(x, y, _texture, screen, &_sprites[directionFacing][ANIM_ATTACK]);
    return;
  }
  else if(attacking)
    attacking = false;
  
  if(xVel == 0.0f && yVel == 0.0f)
    ApplySurface(x, y, _texture, screen, &_sprites[directionFacing][ANIM_NO_FOOT]);
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
    ApplySurface(x, y, _texture, screen, &_sprites[directionFacing][_animationStage]);
  }
}

void Character::Update(void) {
  Move();

  if(_speachBubble.size() != 0) {
    if(_speachBubbleTimer.GetTicks() > SPEACH_BUBBLE_DISPLAY_LENGTH) {
      _speachBubble.pop_front();

      if(_speachBubble.size() != 0) {
        _speachBubbleTimer.Start();
      }
    } else {
      if(_speachBubble.front() != _speachBubbleText.GetText()) {
        _speachBubbleText.SetTextBlended(_speachBubble.front(), small, 0, 0, 0);
      }
    }
  }
}

void Character::Move(void) {
  x += xVel;
  tileX = ((x + (w / 2)) / TILE_WIDTH);
  tileY = ((y + (h / 2)) / TILE_HEIGHT);

  // Check collisions.
  if((x < 0) || (x + w) > levelWidth)                               x -= xVel;
  if(CheckTileCollisions())                                         x -= xVel;
  if(CheckEntityCollisions())                                       x -= xVel;
  if(CheckCharacterCollisions())                                    x -= xVel;

  y += yVel;
  tileX = ((x + (w / 2)) / TILE_WIDTH);
  tileY = ((y + (h / 2)) / TILE_HEIGHT);

  if((y < 0) || (y + h) > levelHeight)                               y -= yVel;
  if(CheckTileCollisions())                                          y -= yVel;
  if(CheckEntityCollisions())                                        y -= yVel;
  if(CheckCharacterCollisions())                                     y -= yVel;
}

/*
 * Bounds checking only included in map.GetTileSolidity() and
 * map.GetEntitySolidity(). Remember to add bounds checking
 * if any other map method is used in a similar manner.
 */
bool Character::CheckTileCollisions(void) {
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      if(map->GetTileSolidity(tileX + i, tileY + j))
        if(CheckCollisionXY(x, y, w, h, map->GetTileX(tileX + i, tileY + j),
                            map->GetTileY(tileX + i, tileY + j), TILE_WIDTH, TILE_HEIGHT))
          return true;
    }
  }
  return false;
}

bool Character::CheckEntityCollisions(void) {
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      if(map->GetEntitySolidity(tileX + i, tileY + j)) {
        if(CheckCollisionXY(x, y, w, h, map->GetEntityX(tileX + i, tileY + j),
                            map->GetEntityY(tileX + i, tileY + j),
                            map->GetEntityWidth(tileX + i, tileY + j),
                            map->GetEntityHeight(tileX + i, tileY + j)))
          return true;
      }
    }
  }
  return false;
}

bool Character::CheckCharacterCollisions(void) {
  for(collisionIter = collisionList.begin();
      collisionIter != collisionList.end();
      collisionIter++) {
    if((*collisionIter) != this) {
      if(CheckCollisionXY(x, y, w, h,
                          (*collisionIter)->GetX(),
                          (*collisionIter)->GetY(),
                          (*collisionIter)->GetWidth(),
                          (*collisionIter)->GetHeight())) {
        return true;
      }
    }
  }
  return false;
}
