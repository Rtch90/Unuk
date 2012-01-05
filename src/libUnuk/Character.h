#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <list>

#include "../Unuk/Globals.h"
#include "../Unuk/Constants.h"
#include "MemClass.h"
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
  
  float GetX(void)                   	{ return x; }
  float GetY(void)                  	{ return y; }
  float GetWidth(void)               	{ return w; }
  float GetHeight(void)             	{ return h; }
  
  void SetXY(float xArg, float yArg)	{ x = xArg, y = yArg; }
  void SetXVelocity(float arg)        { xVel = arg; }
  void SetYVelocity(float arg)      	{ yVel = arg; }

  void SetHealth(int health)          { _health = health; }
  int GetHealth(void)                 { return _health; }
  
  void AddSpeachBubble(string text);

  void Render(void);
  void Update(void);

  inline void* operator new(size_t size) {
    return gMemManager.Allocate(size);
  }

  inline void operator delete(void* object) {
    gMemManager.Free(object);
  }

  inline void* operator new [](size_t size) {
    return gMemManager.Allocate(size);
  }

  inline void operator delete [](void* object) {
    gMemManager.Free(object);
  }
  
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
  
  Timer attackTimer;
  bool attacking;

  int _health;
  
  Map* map;
  
  static const float CHARACTER_SPEED;
  
  int directionFacing;
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
  
  SDL_Surface* _texture;
  
  // [direction][action]
  SDL_Rect _sprites[4][4];
  
  Timer _animationTimer;
  int _animationStage;
  bool _leftFoot;

  list<string> _speachBubble;
  list<string>::iterator _speachBubbleIter;
  Timer _speachBubbleTimer;
  Text _speachBubbleText;
};

#endif
