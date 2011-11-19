#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../Unuk/Globals.h"
#include "Input.h"
#include "Text.h"
#include "Rect.h"

class Button {
public:
  Button(void);
  ~Button(void);

  void SetOutRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetOverRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetXY(int xArg, int yArg);

  void SetTextRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetText(string textArg);

  int GetX(void)          { return x; }
  int GetY(void)          { return y; }
  int GetWidth(void)      { return w; }
  int GetHeight(void)     { return h; }

  bool CheckMouseOver(void);

  void Render(void);

private:
  SDL_Color m_mouseOutColour;
  SDL_Color m_mouseOverColour;
  SDL_Color m_textColour;

  int x;
  int y;
  int w;
  int h;

  Rect button;
  Text text;
};

#endif
