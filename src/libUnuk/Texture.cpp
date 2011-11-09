#include "Texture.h"

Texture::Texture(void) {
  texture = NULL;
}

Texture::~Texture(void) {
  assert(texture != NULL);
  SDL_FreeSurface(texture);
}

void Texture::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
}

void Texture::Render(void) {
  ApplySurface(x, y, texture, screen);
}

void Texture::Render(int xArg, int yArg) {
  ApplySurface(xArg, yArg, texture, screen);
}

void Texture::RenderLiteral(void) {
  ApplySurfaceLiteral(x, y, texture, screen);
}

void Texture::RenderLiteral(int xArg, int yArg) {
  ApplySurfaceLiteral(xArg, yArg,texture, screen);
}

void Texture::Load(const char* filename) {
  if(texture != NULL) {
    // Free the texture.
    SDL_FreeSurface(texture);
  }
  // Load the texture.
  texture = LoadImage(filename);
}

void Texture::LoadAlpha(const char* filename) {
  if(texture != NULL) {
    // Free the texture.
    SDL_FreeSurface(texture);
  }
  // Load the texture with an alpha channel.
  texture = LoadImageAlpha(filename);
}

void Texture::SetAlpha(int alphaArg) {
  SDL_SetAlpha(texture, SDL_SRCALPHA, alphaArg);
}
