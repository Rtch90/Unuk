#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "../Unuk/Globals.h"
#include "ImageLoader.h"
#include "ApplySurface.h"

class Texture {
public:
  Texture(void);
  ~Texture(void);

  int GetWidth(void)    { return texture->w; }
  int GetHeight(void)   { return texture->h; }
  int GetX(void)        { return x; }
  int GetY(void)        { return y; }

  void SetXY(int xArg, int yArg);

  void Render(void);
  void Render(int xArg, int yArg);

  void RenderLiteral(void);
  void RenderLiteral(int xArg, int yArg);

  void Load(const char* filename);
  void LoadAlpha(const char* filename);
  void SetAlpha(int alphaArg);

protected:
  int x, y;

private:
  SDL_Surface* texture;
};

#endif
