#include "Collision.h"

bool CheckCollisionRect(SDL_Rect a, SDL_Rect b) {
  if(a.y + a.h <= b.y)
    return false;
  if(a.y >= b.y + b.h)
    return false;
  if(a.x + a.w <= b.x)
    return false;
  if(a.x >= b.x + b.w)
    return false;

  return true;
}

bool CheckCollisionXY(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  if(y1 + h1 <= y2)
    return false;
  if(y1 >= y2 + h2)
    return false;
  if(x1 + w1 <= x2)
    return false;
  if(x1 >= x2 + w2)
    return false;

  return true;
}
