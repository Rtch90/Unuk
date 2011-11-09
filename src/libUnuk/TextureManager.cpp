#include "TextureManager.h"

TextureManager::TextureManager(void) {
  m_allocated = 0;
}

TextureManager::~TextureManager(void) {
  Clear();
}

void TextureManager::Clear(void) {
  for(int i = 0; i < m_allocated; i++) {
    SDL_FreeSurface(array[i].texture);
    array[i].name.clear();
  }
  m_allocated = 0;
}

int TextureManager::Add(string filename) {
  assert(m_allocated < TEXTURE_NODE_SIZE);

  // Has the texture been loaded already?
  for(int i = 0; i < m_allocated; i++) {
    if(array[i].name == filename) {
      return i;
    }
  }

  array[m_allocated].name = filename;
  array[m_allocated].texture = LoadImage(filename.c_str());

  return m_allocated++;
}

int TextureManager::AddAlpha(string filename) {
  assert(m_allocated < TEXTURE_NODE_SIZE);

  // Has the texture been loaded already?
  for(int i = 0; i < m_allocated; i++) {
    if(array[i].name == filename) {
      return i;
    }
  }

  array[m_allocated].name = filename;
  array[m_allocated].texture = LoadImageAlpha(filename.c_str());

  return m_allocated++;
}
