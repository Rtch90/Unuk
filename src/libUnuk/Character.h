#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <list>

#include "../Unuk/Globals.h"
#include "../Unuk/Constants.h"
#include "ApplySurface.h"
#include "ImageLoader.h"
#include "Collision.h"
#include "Map.h"
#include "Timer.h"
#include "Text.h"
#include "Debug.h"
using namespace std;

class Map;

class Character {
public:
  Character(Map* mapArg);
  ~Character(void);

  void LoadSprites(string filename, int wArg, int hArg);
  
  float GetX(void) 		{ return x; }
  float GetY(void)		{ return y; }
  float GetWidth(void)		{ return w; }
  float GetHeight(void)		{ return h; }
  
  void SetXY(float xArg, float yArg)		{ x = xArg, y = yArg; }
  void SetXVelocity(float arg)			{ xVel = arg; }
  void SetYVelocity(float arg)			{ yVel = arg; }
  
  void AddSpeachBubble(string text);

  void Render(void);
  void Update(void);
  
protected:
  void Move(void);
  
  bool CheckTileCollisions(void);
  bool CheckEntityCollisions(void);
  bool CheckCharacterCollisions(void);
  
  float x;
  float y;
  float w;
  float h;
  
  float xVel;
  float yVel;
  
  int tileX;
  int tileY;
  
  Timer m_attackTimer;
  bool m_attacking;
  
  Map* map;
  
  static const float CHARACTER_SPEED;
  
  int m_directionFacing;
  static const int FACING_UP     = 0;
  static const int FACING_RIGHT  = 1;
  static const int FACING_DOWN   = 2;
  static const int FACING_LEFT   = 3;
  
  static const int ANIM_LEFT_FOOT    = 0;
  static const int ANIM_NO_FOOT      = 1;
  static const int ANIM_RIGHT_FOOT   = 2;
  static const int ANIM_ATTACK       = 3;
  
private:
  static const int ANIMATION_SPEED         = 200;
  static const int ATTACKING_DISPLAY_LEN   = 150;

  static const int SPEACH_BUBBLE_DISPLAY_LENGTH = 6000;
  
  SDL_Surface* m_texture;
  
  // [direction][action]
  SDL_Rect sprites[4][4];
  
  Timer m_animationTimer;
  int m_animationStage;
  bool m_leftFoot;

  list<string> m_speachBubble;
  list<string>::iterator m_speachBubbleIter;
  Timer m_speachBubbleTimer;
  Text m_speachBubbleText;
};

#endif
