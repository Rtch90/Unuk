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
 * and it will return the teture if it is already in memory
 * or load the tture if it is not.
 */
class TextureManager {
public:
  TextureManager(void);
  ~TextureManager(void);

  void Unload(void);

  SDL_Surface* Add(string filename);
  SDL_Surface* AddAlpha(string filename);

private:
  // The textureNode will hold the name and the texture.
  struct textureNode {
    SDL_Surface* texture;
    string name;
  };

  // We should not need more than a hundred..
  static const int TEXTURE_ARR_SIZE = 100;
  textureNode _textures[TEXTURE_ARR_SIZE];

  int _allocated;
};

#endif
