#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <list>

#include "../../Unuk/Globals.h"
#include "../../Unuk/Constants.h"
#include "../Engine/MemClass.h"
#include "../Sprite/ApplySurface.h"
#include "../Sprite/ImageLoader.h"
#include "../Engine/Collision.h"
#include "../LevelGen/LevelGen.h"
#include "../System/Timer.h"
#include "../UI/Text.h"
#include "../UI/Bar.h"
#include "../System/Debug.h"
using namespace std;

class LevelGen;

class Character {
public:
	Character(LevelGen* mapArg);
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

	int  GetDirectionFacing(void)       { return directionFacing; }
	void SetDirectionFacing(int dir)    { directionFacing = dir;  }

	void Render(void);
	void Update(void);

	void OnAttack(void);

//	inline void* operator new(size_t size) {
//		return gMemManager.Allocate(size);
//	}
//
//	inline void operator delete(void* object) {
//		gMemManager.Free(object);
//	}
//
//	inline void* operator new [](size_t size) {
//		return gMemManager.Allocate(size);
//	}
//
//	inline void operator delete [](void* object) {
//		gMemManager.Free(object);
//	}
  
  enum {
    FACING_UP,
    FACING_RIGHT,
    FACING_DOWN,
    FACING_LEFT
  };

protected:
	void HealthBarScroll(void);

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

	LevelGen* map;

	static const float CHARACTER_SPEED;

	int directionFacing;

	static const int ANIM_LEFT_FOOT    = 0;
	static const int ANIM_NO_FOOT      = 1;
	static const int ANIM_RIGHT_FOOT   = 2;
	static const int ANIM_ATTACK       = 3;

	Bar _healthBar;
	Timer _healthBarDuration;
	bool _showHealthBar;

private:
	static const int ANIMATION_SPEED         = 200;
	static const int ATTACKING_DISPLAY_LEN   = 150;

	SDL_Surface* _texture;

	// [direction][action]
	SDL_Rect _sprites[4][4];

	Timer _animationTimer;
	int _animationStage;
	bool _leftFoot;
};
