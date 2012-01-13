#pragma once
#include <SDL/SDL.h>
#include <string>

#include "../../Unuk/Globals.h"
#include "../Sprite/ApplySurface.h"
#include "../Sprite/TextureManager.h"

class MapElement {
public:
  MapElement(void);
  ~MapElement(void);

  static void SetTextureManager(TextureManager* arg);

  virtual void SetTexture(SDL_Surface* arg);
  virtual void Render(void);
  virtual void Update(void);

  void SetSolidity(bool arg);
  bool GetSolidity(void);

  void SetXY(int xArg, int yArg);
  int GetX(void);
  int GetY(void);
  int GetWidth(void);
  int GetHeight(void);

protected:
  SDL_Surface* _texture;

  bool _solid;

  int x;
  int y;
};
