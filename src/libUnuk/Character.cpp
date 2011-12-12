#include "Character.h"

// Pixels * 60 / sec
const float Character::CHARACTER_SPEED = 3.5f;

static list<Character*>collisionList;
static list<Character*>::iterator collisionIterator;

Character::Character(Map* mapArg) {
  map = mapArg;
  m_attacking = false;
  m_directionFacing = FACING_DOWN;
  m_animationStage  = ANIM_NO_FOOT;
  m_animationTimer.Start();
  m_leftFoot = false;
  
  xVel = 0.0f;
  yVel = 0.0f;
  
  m_texture = NULL;
  
  collisionList.push_front(this);
}

Character::~Character(void) {
  SDL_FreeSurface(m_texture);
  for(collisionIterator = collisionList.begin(); collisionIterator != collisionList.end(); collisionIterator++) {
    if((*collisionIterator) == this) {
      collisionList.erase(collisionIterator);
      break;
    }
  }
}

void Character::Render(void) {
  if(m_attacking && m_attackTimer.GetTicks() < ATTACKING_DISPLAY_LEN) {
    ApplySurface(x, y, m_texture, screen, &sprites[m_directionFacing][ANIM_ATTACK]);
    return;
  }
  else if(m_attacking)
    m_attacking = false;
  
  if(xVel == 0.0f && yVel == 0.0f)
    ApplySurface(x, y, m_texture, screen, &sprites[m_directionFacing][ANIM_NO_FOOT]);
  else {
    if(m_animationTimer.GetTicks() > ANIMATION_SPEED) {
      if(m_animationStage == ANIM_NO_FOOT) {
        if(m_leftFoot == true)
          m_animationStage = ANIM_RIGHT_FOOT;
        else
          m_animationStage = ANIM_LEFT_FOOT;
      }
      else if(m_animationStage == ANIM_LEFT_FOOT) {
        m_animationStage = ANIM_NO_FOOT;
        m_leftFoot = true;
      }
      else if(m_animationStage == ANIM_RIGHT_FOOT) {
        m_animationStage = ANIM_NO_FOOT;
        m_leftFoot = false;
      }
      m_animationTimer.Start();
    }
    ApplySurface(x, y, m_texture, screen, &sprites[m_directionFacing][m_animationStage]);
  }
}

void Character::LoadSprites(string filename, int wArg, int hArg) {
  if(m_texture != NULL)
    SDL_FreeSurface(m_texture);

  m_texture = LoadImageAlpha(filename.c_str());

  w = wArg;
  h = hArg;

  for(int m_direction = 0; m_direction < 4; m_direction++) {
    for(int m_action = 0; m_action < 4; m_action++) {
      sprites[m_direction][m_action].x = w * m_action;
      sprites[m_direction][m_action].y = h * m_direction;
      sprites[m_direction][m_action].w = w;
      sprites[m_direction][m_action].h = h;
    }
  }
}

void Character::Update(void) {
  Move();
}

void Character::Move(void) {
  x += xVel;
  tileX = ((x + (w / 2)) / TILE_WIDTH);
  tileY = ((y + (h / 2)) / TILE_HEIGHT);

  if((x < 0) || (x + w) > levelWidth)
    x -= xVel;
  if(CheckTileCollisions())
    x -= xVel;
  if(CheckEntityCollisions())
    x -= xVel;
  if(CheckCharacterCollisions())
    x -= xVel;

  y += yVel;
  tileX = ((x + (w / 2)) / TILE_WIDTH);
  tileY = ((y + (h / 2)) / TILE_HEIGHT);

  if((y < 0) || (y + h) > levelHeight)
    y -= yVel;
  if(CheckTileCollisions())
    y -= yVel;
  if(CheckEntityCollisions())
    y -= yVel;
  if(CheckCharacterCollisions())
    y -= yVel;
}

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
        printf("\nw - ", map->GetEntityWidth(tileX + i, tileY + j));
        printf("\nh - ", map->GetEntityHeight(tileX + i, tileY + j));
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
  for(collisionIterator = collisionList.begin();
      collisionIterator != collisionList.end();
      collisionIterator++) {
    if((*collisionIterator) != this) {
      if(CheckCollisionXY(x, y, w, h,
                          (*collisionIterator)->GetX(),
                          (*collisionIterator)->GetY(),
                          (*collisionIterator)->GetWidth(),
                          (*collisionIterator)->GetHeight())) {
        return true;
      }
    }
  }
  return false;
}
