#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <list>

#include "../Unuk/Globals.h"
#include "ApplySurface.h"
#include "Font.h"
#include "Debug.h"
using namespace std;

enum textSizes_t { vsmall, small, medium, large, vlarge };

class Text {
public:
  Text(void);
  ~Text(void);

  static void LoadFonts(void);
  static void FreeFonts(void);

  int GetWidth(void)          { return w; }
  int GetHeight(void)         { return h; }
  int GetX(void)              { return x; }
  int GetY(void)              { return y; }

  SDL_Color GetColour(void)   { return _textColour; }

  void SetXY(int xArg, int yArg);

  int GetLineWidth()                  { return lineWidth; }
  void SetLineWidth(int lineWidthArg) { lineWidth = lineWidthArg; }

  int SetTextBlended(string textArg, textSizes_t size, SDL_Color, bool wordWrap=false);
  int SetTextBlended(string textArg, textSizes_t size, Uint8 r, Uint8 g, Uint8 b, bool wordWrap=false);
  int SetTextShaded(string textArg, textSizes_t size, SDL_Color, SDL_Color, bool wordWrap=false);
  int SetTextShaded(string textArg, textSizes_t size, Uint8 rF, Uint8 gF, Uint8 bF, Uint8 rB, Uint8 gB, Uint8 bB, bool wordWrap=false);

  string GetText(void)        { return _textContents; }

  void Render(void);
  void Render(int xArg, int yArg);
  void RenderLiteral(void);
  void RenderLiteral(int xArg, int yArg);

private:
  int x, y, w, h;
  int lineWidth;

  string _textContents;
  SDL_Color _textColour;
  std::list<SDL_Surface*> _lines;

  std::string DoWordWrap(TTF_Font* fontArg, const std::string& textArg);

  static TTF_Font* vSmallFont;
  static TTF_Font* smallFont;
  static TTF_Font* mediumFont;
  static TTF_Font* largeFont;
  static TTF_Font* vLargeFont;
};
