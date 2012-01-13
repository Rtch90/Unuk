#include "TextureManager.h"

TextureManager::TextureManager(void) {
  _allocated = 0;
}

TextureManager::~TextureManager(void) {
  Unload();
}

void TextureManager::Unload(void) {
  for(int i = 0; i < _allocated; i++) {
    SDL_FreeSurface(_textures[i].texture);
    _textures[i].name.clear();
  }
  _allocated = 0;
}

SDL_Surface* TextureManager::Add(string filename) {
  assert(_allocated < TEXTURE_ARR_SIZE - 1);

  // Has the texture been loaded already?
  for(int i = 0; i < _allocated; i++) {
    if(_textures[i].name == filename) {
      return _textures[i].texture;
    }
  }
  // If not, then load it.
  _textures[_allocated].name = filename;
  _textures[_allocated].texture = LoadImage(filename.c_str());

  _allocated++;

  return _textures[_allocated - 1].texture;
}

SDL_Surface* TextureManager::AddAlpha(string filename) {
  assert(_allocated < TEXTURE_ARR_SIZE - 1);

  // Has the texture been loaded already?
  for(int i = 0; i < _allocated; i++) {
    if(_textures[i].name == filename) {
      return _textures[i].texture;
    }
  }

  // If not, then load it.

  _textures[_allocated].name = filename;
  _textures[_allocated].texture = LoadImageAlpha(filename.c_str());

  _allocated++;

  return _textures[_allocated -1].texture;
}
