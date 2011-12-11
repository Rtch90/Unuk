#include "Rect.h"

Rect::Rect(void) {
}

Rect::~Rect(void) {
}

void Rect::SetXY(int xArg, int yArg) {
  rect.x = xArg;
  rect.y = yArg;
}

void Rect::SetWidthHeight(int wArg, int hArg) {
  rect.w = wArg;
  rect.h = hArg;
}

void Rect::SetRGB(Uint8 rArg, Uint8 gArg, Uint8 bArg) {
  r = rArg;
  g = gArg;
  b = bArg;
}

void Rect::SetRGB(SDL_Color colour) {
  r = colour.r;
  g = colour.g;
  b = colour.b;
}

void Rect::Draw(void) {
  SDL_Rect offset;

  offset.x = rect.x - camera.x;
  offset.y = rect.y - camera.y;
  offset.w = rect.w;
  offset.h = rect.h;

  SDL_FillRect(screen, &offset, SDL_MapRGB(screen->format, r, g, b));
}

void Rect::Draw(int xArg, int yArg) {
  SDL_Rect offset;

  offset.x = xArg - camera.x;
  offset.y = yArg - camera.y;
  offset.w = rect.w;
  offset.h = rect.h;
}

void Rect::DrawLiteral(void) {
  SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, r, g, b));
}

void Rect::DrawLiteral(int xArg, int yArg) {
  SDL_Rect offset;

  offset.x = xArg;
  offset.y = yArg;
  offset.w = rect.w;
  offset.h = rect.h;

  SDL_FillRect(screen, &offset, SDL_MapRGB(screen->format, r, g, b));
}
