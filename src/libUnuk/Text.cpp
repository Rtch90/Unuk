#include "Text.h"

TTF_Font* Text::vSmallFont   = NULL;
TTF_Font* Text::smallFont    = NULL;
TTF_Font* Text::mediumFont   = NULL;
TTF_Font* Text::largeFont    = NULL;
TTF_Font* Text::vLargeFont   = NULL;

Text::Text(void) {
  _text = NULL;
}

Text::~Text(void) {
  assert(_text != NULL);
  SDL_FreeSurface(_text);
}

void Text::LoadFonts(void) {
  // Load the fonts if they are not already in memory.
  assert(vSmallFont == NULL);
  assert(smallFont == NULL);
  assert(mediumFont == NULL);
  assert(largeFont == NULL);
  assert(vLargeFont == NULL);

  vSmallFont      = Font("../Data/Media/Fonts/Enigma_2.ttf", 16);
  smallFont       = Font("../Data/Media/Fonts/Enigma_2.ttf", 23);
  mediumFont      = Font("../Data/Media/Fonts/Enigma_2.ttf", 27);
  largeFont       = Font("../Data/Media/Fonts/Enigma_2.ttf", 32);
  vLargeFont      = Font("../Data/Media/Fonts/Enigma_2.ttf", 48);
}

void Text::FreeFonts(void) {
  // If the fonts are loaded, then free them.
  assert(vSmallFont != NULL);
  assert(smallFont != NULL);
  assert(mediumFont != NULL);
  assert(largeFont != NULL);
  assert(vLargeFont != NULL);

  TTF_CloseFont(vSmallFont);
  TTF_CloseFont(smallFont);
  TTF_CloseFont(mediumFont);
  TTF_CloseFont(largeFont);
  TTF_CloseFont(vLargeFont);
}

void Text::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
}

int Text::SetTextBlended(string textArg, textSizes_t size, SDL_Color colour) {
  _textContents = textArg;

  if(_text != NULL) {
    SDL_FreeSurface(_text);
  }

  if(size == vsmall) {
    _text = TTF_RenderText_Blended(vSmallFont, textArg.c_str(), colour);
    return 1;
  }
  else if(size == small) {
    _text = TTF_RenderText_Blended(smallFont, textArg.c_str(), colour);
    return 1;
  }
  else if(size == medium) {
    _text = TTF_RenderText_Blended(mediumFont, textArg.c_str(), colour);
    return 1;
  }
  else if(size == large) {
    _text = TTF_RenderText_Blended(largeFont, textArg.c_str(), colour);
    return 1;
  } else {
    _text = TTF_RenderText_Blended(vLargeFont, textArg.c_str(), colour);
    return 1;
  }
}

int Text::SetTextBlended(string textArg, textSizes_t size, Uint8 r, Uint8 g, Uint8 b) {
  SDL_Color f = { r, g, b };
  return SetTextBlended(textArg, size, f);
}

int Text::SetTextShaded(string textArg, textSizes_t size, SDL_Color colour, SDL_Color bgColour) {
  _textContents = textArg;

  if(_text != NULL) {
    SDL_FreeSurface(_text);
  }

  if(size == vsmall) {
    _text = TTF_RenderText_Shaded(vSmallFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
  else if(size == small) {
    _text = TTF_RenderText_Shaded(smallFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
  else if(size == medium) {
    _text = TTF_RenderText_Shaded(mediumFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
  else if(size == large) {
    _text = TTF_RenderText_Shaded(largeFont, textArg.c_str(), colour, bgColour);
    return 1;
  } else {
    _text = TTF_RenderText_Shaded(vLargeFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
}

int Text::SetTextShaded(string textArg, textSizes_t size, Uint8 rF, Uint8 gF, Uint8 bF, Uint8 rB, Uint8 gB, Uint8 bB) {
  SDL_Color f = { rF, gF, bF };
  SDL_Color b = { rB, gB, bB };
  return SetTextShaded(textArg, size, f, b);
}

void Text::Render(void) {
  ApplySurface(x, y, _text, screen);
}

void Text::Render(int xArg, int yArg) {
  ApplySurface(xArg, yArg, _text, screen);
}

void Text::RenderLiteral(void) {
  ApplySurfaceLiteral(x, y, _text, screen);
}

void Text::RenderLiteral(int xArg, int yArg) {
  ApplySurfaceLiteral(xArg, yArg, _text, screen);
}
