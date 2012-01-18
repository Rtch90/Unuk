#include "Rect.h"

Rect::Rect(void) {
}

Rect::~Rect(void) {
}

void Rect::SetXY(int xArg, int yArg) {
  rect.x = (Sint16)xArg;
  rect.y = (Sint16)yArg;
}

void Rect::SetWidthHeight(int wArg, int hArg) {
  rect.w = (Uint16)wArg;
  rect.h = (Uint16)hArg;
}

void Rect::SetRGBA(Uint8 rArg, Uint8 gArg, Uint8 bArg, Uint8 aArg) {
  r = rArg;
  g = gArg;
  b = bArg;
  a = aArg;
}

void Rect::SetRGB(Uint8 rArg, Uint8 gArg, Uint8 bArg) {
  r = rArg;
  g = gArg;
  b = bArg;
  a = 255;
}

void Rect::SetRGB(SDL_Color colour) {
  r = colour.r;
  g = colour.g;
  b = colour.b;
  a = 255;
}

void Rect::Draw(void) {
  SDL_Rect offset;

  offset.x = rect.x - camera.x;
  offset.y = rect.y - camera.y;
  offset.w = rect.w;
  offset.h = rect.h;

  SDL_FillRect(screen, &offset, SDL_MapRGBA(screen->format, r, g, b, a));
}

void Rect::Draw(int xArg, int yArg) {
  SDL_Rect offset;

  offset.x = (Sint16)(xArg - camera.x);
  offset.y = (Sint16)(yArg - camera.y);
  offset.w = (Sint16)rect.w;
  offset.h = (Sint16)rect.h;

  SDL_FillRect(screen, &offset, SDL_MapRGBA(screen->format, r, g, b, a));
}

void Rect::DrawLiteral(void) {
  SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, r, g, b, a));
}

void Rect::DrawLiteral(int xArg, int yArg) {
  SDL_Rect offset;

  offset.x = (Sint16)xArg;
  offset.y = (Sint16)yArg;
  offset.w = rect.w;
  offset.h = rect.h;

  SDL_FillRect(screen, &offset, SDL_MapRGBA(screen->format, r, g, b, a));
}
