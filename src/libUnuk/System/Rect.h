#pragma once
#include <SDL/SDL.h>
#include "../../Unuk/Globals.h"
#include "../Sprite/ApplySurface.h"
using namespace std;

class Rect {
public:
  Rect(void);
  ~Rect(void);

  int GetWidth(void)  { return rect.w; }
  int GetHeight(void) { return rect.h; }
  int GetX(void)      { return rect.x; }
  int GetY(void)      { return rect.y; }

  void SetXY(int xArg, int yArg);
  void SetWidthHeight(int wArg, int hArg);

  void SetRGBA(Uint8 rArg, Uint8 gArg, Uint8 bArg, Uint8 aArg);
  void SetRGB(Uint8 rArg, Uint8 gArg, Uint8 bArg);
  void SetRGB(SDL_Color);

  void Draw(void);
  void Draw(int xArg, int yArg);
  void DrawLiteral(void);
  void DrawLiteral(int xArg, int yArg);

protected:
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;

private:
  SDL_Rect rect;
};
