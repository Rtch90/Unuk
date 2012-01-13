#include "MapElement.h"

MapElement::MapElement(void) {

}

MapElement::~MapElement(void) {

}

void MapElement::SetTexture(SDL_Surface* arg) {
  _texture = arg;
}

void MapElement::Render(void) {
  ApplySurface(x, y, _texture, screen);
}

void MapElement::Update(void) {

}

void MapElement::SetSolidity(bool arg) {
  _solid = arg;
}

bool MapElement::GetSolidity(void) {
  return _solid;
}

void MapElement::SetXY(int xArg, int yArg) {
  x = xArg,
  y = yArg;
}

int MapElement::GetX(void)        { return x; }
int MapElement::GetY(void)        { return y; }
int MapElement::GetWidth(void)    { return _texture->w; }
int MapElement::GetHeight(void)   { return _texture->h; }
