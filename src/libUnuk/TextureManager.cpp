#include "TextureManager.h"

TextureManager::TextureManager(void) {
  m_allocated = 0;
}

TextureManager::~TextureManager(void) {
  Unload();
}

void TextureManager::Unload(void) {
  for(int i = 0; i < m_allocated; i++) {
    SDL_FreeSurface(textures[i].texture);
    textures[i].name.clear();
  }
  m_allocated = 0;
}

SDL_Surface* TextureManager::Add(string filename) {
  assert(m_allocated < TEXTURE_ARR_SIZE - 1);

  // Has the texture been loaded already?
  for(int i = 0; i < m_allocated; i++) {
    if(textures[i].name == filename) {
      return textures[i].texture;
    }
  }
  // If not, then load it.
  textures[m_allocated].name = filename;
  textures[m_allocated].texture = LoadImage(filename.c_str());

  m_allocated++;

  return textures[m_allocated - 1].texture;
}

SDL_Surface* TextureManager::AddAlpha(string filename) {
  assert(m_allocated < TEXTURE_ARR_SIZE - 1);

  // Has the texture been loaded already?
  for(int i = 0; i < m_allocated; i++) {
    if(textures[i].name == filename) {
      return textures[i].texture;
    }
  }

  // If not, then load it.

  textures[m_allocated].name = filename;
  textures[m_allocated].texture = LoadImageAlpha(filename.c_str());

  m_allocated++;

  return textures[m_allocated -1].texture;
}
