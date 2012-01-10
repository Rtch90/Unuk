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

  void SetHighlightRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetHighlightRGB(SDL_Color);

  void SetHighlighted(bool highlighted);

  void SetXY(int xArg, int yArg);

  int GetX(void)        const     { return x; }
  int GetY(void)        const     { return y; }
  int GetWidth(void)    const     { return w; }
  int GetHeight(void)   const     { return h; }

  bool GetHighlighted(void) { return _highlighted; }

  bool CheckMouseOver(void);

  void Render(void);
  void Render(int xArg, int yArg);
  void RenderLiteral(void);
  void RenderLiteral(int xArg, int yArg);

private:
  SDL_Color _mouseOutColour;
  SDL_Color _mouseOverColour;
  SDL_Color _textColour;
  SDL_Color _highlightColour;

  int x;
  int y;
  int w;
  int h;

  Rect _button;
  Text _text;

  bool _highlighted;

  bool _mouseOver;
};

#endif
