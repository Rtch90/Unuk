#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_
#include <SDL/SDL.h>
#include <string>
#include <assert.h>
#include "ImageLoader.h"
using namespace std;

/*
 * The Texture Manager will keep a small "Database"
 * of the name of the texture that is loaded and the
 * actual texture so we can query it with the filename
 * and it will return an index that we can use to retrieve
 * the texture.
 */
class TextureManager {
public:
  TextureManager(void);
  ~TextureManager(void);

  SDL_Surface* Get(int n)      { return array[n].texture; }
  int GetTextureWidth(int n)   { return array[n].texture->w; }
  int GetTextureHeight(int n)  { return array[n].texture->h; }

  void Clear(void);

  int Add(string filename);
  int AddAlpha(string filename);

private:
  // The textureNode will hold the name and the texture.
  struct textureNode {
    SDL_Surface* texture;
    string name;
  };

  // We should not need more than a hundred..
  static const int TEXTURE_NODE_SIZE = 100;
  textureNode array[TEXTURE_NODE_SIZE];

  int m_allocated;
};

#endif
