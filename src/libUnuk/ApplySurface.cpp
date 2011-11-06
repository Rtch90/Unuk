#include "ApplySurface.h"

void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
  assert(source != NULL);

  SDL_Rect offset;

  offset.x = x - camera.x;
  offset.y = y - camera.y;

  SDL_BlitSurface(source, clip, destination, &offset);
}

void ApplySurfaceLiteral(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
  assert(source != NULL);

  SDL_Rect offset;

  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(source, clip, destination, &offset);
}
