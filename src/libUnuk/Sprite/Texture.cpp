#include "Texture.h"

Texture::Texture(void) {
  _texture = NULL;
}

Texture::~Texture(void) {
  assert(_texture != NULL);
  SDL_FreeSurface(_texture);
}

void Texture::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
}

void Texture::Render(void) {
  ApplySurface(x, y, _texture, screen);
}

void Texture::Render(int xArg, int yArg) {
  ApplySurface(xArg, yArg, _texture, screen);
}

void Texture::RenderLiteral(void) {
  ApplySurfaceLiteral(x, y, _texture, screen);
}

void Texture::RenderLiteral(int xArg, int yArg) {
  ApplySurfaceLiteral(xArg, yArg,_texture, screen);
}

void Texture::Load(const char* filename) {
  if(_texture != NULL) {
    // Free the texture.
    SDL_FreeSurface(_texture);
  }
  // Load the texture.
  _texture = LoadImage(filename);
}

void Texture::LoadAlpha(const char* filename) {
  if(_texture != NULL) {
    // Free the texture.
    SDL_FreeSurface(_texture);
  }
  // Load the texture with an alpha channel.
  _texture = LoadImageAlpha(filename);
}

void Texture::SetAlpha(int alphaArg) {
  SDL_SetAlpha(_texture, SDL_SRCALPHA, (Uint8)alphaArg);
}
