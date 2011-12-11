#ifndef _TEXT_H_
#define _TEXT_H_
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "../Unuk/Globals.h"
#include "ApplySurface.h"
#include "Font.h"
#include "Debug.h"
using namespace std;

class Text {
public:
  Text(void);
  ~Text(void);

  static void LoadFonts(void);
  static void FreeFonts(void);

  int GetWidth(void)          { return m_text->w; }
  int GetHeight(void)         { return m_text->h; }
  int GetX(void)              { return x; }
  int GetY(void)              { return y; }

  string GetText(void)        { return m_textContents; }
  SDL_Color GetColour(void)   { return m_textColour; }

  void SetXY(int xArg, int yArg);

  int SetTextBlended(string textArg, string size, SDL_Color);
  int SetTextBlended(string textArg, string size, Uint8 r, Uint8 g, Uint8 b);
  int SetTextShaded(string textArg, string size, SDL_Color, SDL_Color);
  int SetTextShaded(string textArg, string size, Uint8 rF, Uint8 gF, Uint8 bF, Uint8 rB, Uint8 gB, Uint8 bB);

  void Render(void);
  void Render(int xArg, int yArg);
  void RenderLiteral(void);
  void RenderLiteral(int xArg, int yArg);

private:
  int x, y, w, h;

  string m_textContents;
  SDL_Color m_textColour;
  SDL_Surface* m_text;

  static TTF_Font* vSmallFont;
  static TTF_Font* smallFont;
  static TTF_Font* mediumFont;
  static TTF_Font* largeFont;
  static TTF_Font* vLargeFont;
};

#endif
