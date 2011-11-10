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
  int SetTextShaded(string textArg, string size, SDL_Color, SDL_Color);

  void Render(void);
  void RenderLiteral(void);

private:
  int x, y, w, h;

  string m_textContents;
  SDL_Color m_textColour;
  SDL_Surface* m_text;

  static TTF_Font* verySmallFont;
  static TTF_Font* smallFont;
  static TTF_Font* mediumFont;
  static TTF_Font* largeFont;
};

#endif
