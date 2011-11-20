#ifndef _COLLISION_H_
#define _COLLISION_H_
#include <SDL/SDL.h>

bool CheckCollisionRect(SDL_Rect a, SDL_Rect b);
bool CheckCollisionXY(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif
