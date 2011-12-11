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
  void SetOutRGB(SDL_Color);
  void SetOverRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetOverRGB(SDL_Color);

  void SetTextRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetTextRGB(SDL_Color);
  void SetText(string textArg);

  void SetXY(int xArg, int yArg);

  int GetX(void)          { return x; }
  int GetY(void)          { return y; }
  int GetWidth(void)      { return w; }
  int GetHeight(void)     { return h; }

  bool CheckMouseOver(void);

  void Render(void);
  void Render(int xArg, int yArg);

private:
  SDL_Color m_mouseOutColour;
  SDL_Color m_mouseOverColour;
  SDL_Color m_textColour;

  int x;
  int y;
  int w;
  int h;

  Rect button;
  Text m_text;
};

#endif
