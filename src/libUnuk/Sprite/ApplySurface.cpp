#include "ApplySurface.h"

void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
  assert(source != NULL);

  SDL_Rect offset;

  offset.x = (Sint16)(x - camera.x);
  offset.y = (Sint16)(y - camera.y);

  SDL_BlitSurface(source, clip, destination, &offset);
}

void ApplySurfaceLiteral(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
  assert(source != NULL);

  SDL_Rect offset;

  offset.x = (Sint16)x;
  offset.y = (Sint16)y;

  SDL_BlitSurface(source, clip, destination, &offset);
}
