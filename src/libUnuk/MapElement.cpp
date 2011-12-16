#include "MapElement.h"

MapElement::MapElement(void) {

}

MapElement::~MapElement(void) {

}

void MapElement::SetTexture(SDL_Surface* arg) {
  m_texture = arg;
}

void MapElement::Render(void) {
  ApplySurface(x, y, m_texture, screen);
}

void MapElement::Update(void) {

}

void MapElement::SetSolidity(bool arg) {
  m_solid = arg;
}

bool MapElement::GetSolidity(void) {
  return m_solid;
}

void MapElement::SetXY(int xArg, int yArg) {
  x = xArg,
  y = yArg;
}

int MapElement::GetX(void)        { return x; }
int MapElement::GetY(void)        { return y; }
int MapElement::GetWidth(void)    { return m_texture->w; }
int MapElement::GetHeight(void)   { return m_texture->h; }
