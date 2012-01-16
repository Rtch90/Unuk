#pragma once
#include <SDL/SDL.h>

#include "../System/Rect.h"

class Bar {
public:
  Bar(void);

  int GetX(void)      const { return x;       }
  int GetY(void)      const { return y;       }
  int GetWidth(void)  const { return width;   }
  int GetHeight(void) const { return height;  }

  void SetXY(int xArg, int yArg);
  void SetWidthHeight(int wArg, int hArg);

  void SetBackgroundRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetBackgroundRGB(SDL_Color colour);

  void SetForegroundRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetForegroundRGB(SDL_Color colour);

  void  SetProgress(float progress);
  float GetProgress(void) { return _progress; }

  void Draw(void);
  void Draw(int xArg, int yArg);
  void DrawLiteral(void);
  void DrawLiteral(int xArg, int yArg);

private:
  Rect _bgRect; // background
  Rect _fgRect; // foreground
  
  float _progress;

  int x;
  int y;
  int width;
  int height;
};
