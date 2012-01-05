#include "Text.h"

TTF_Font* Text::vSmallFont   = NULL;
TTF_Font* Text::smallFont    = NULL;
TTF_Font* Text::mediumFont   = NULL;
TTF_Font* Text::largeFont    = NULL;
TTF_Font* Text::vLargeFont   = NULL;

const static int lineSpacing = 3;

Text::Text(void) {
  x=0;
  y=0;
  w=0;
  h=0;
  lineWidth=50;
}

Text::~Text(void) {
  if(!_lines.empty()) {
    for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
      SDL_FreeSurface(*it);
    }
    _lines.clear();
  }
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

int Text::SetTextBlended(string textArg, textSizes_t size, SDL_Color colour,bool wordWrap) {
  _textContents = textArg;

  if(!_lines.empty()) {
    for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
      SDL_FreeSurface(*it);
    }
    _lines.clear();
  }

  TTF_Font* font = NULL;
  if(size == vsmall) {
    font = vSmallFont;
  } else if(size == small) {
    font = smallFont;
  } else if(size == medium) {
    font = mediumFont;
  } else if(size == large) {
    font = largeFont;
  } else {
    font = vLargeFont;
  }

  std::string finalTextContents = textArg;

  if(wordWrap) {
    finalTextContents = DoWordWrap(font, finalTextContents);
  }
  
  std::list<std::string> lines;
  std::string line;
  for(int i = 0; i < (int)finalTextContents.size(); i++) {
    char c = finalTextContents.at(i);
    if(c=='\n') {
      lines.push_back(line);
      line.clear();
    } else {
      line += c;
    }
  }
  if (!line.empty()) {
    lines.push_back(line);
  }

  for(std::list<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    SDL_Surface* lineSurf = TTF_RenderText_Blended(font, it->c_str(), colour);

    int linePixelWidth;
    int linePixelHeight;
    TTF_SizeText(font, it->c_str(), &linePixelWidth, &linePixelHeight);

    if(linePixelWidth > w) {
      w = linePixelWidth;
    }

    h += linePixelHeight + lineSpacing; 

    _lines.push_back(lineSurf);
  }

  return 1;
}

int Text::SetTextBlended(string textArg, textSizes_t size, Uint8 r, Uint8 g, Uint8 b, bool wordWrap) {
  SDL_Color f = { r, g, b };
  return SetTextBlended(textArg, size, f, wordWrap);
}

int Text::SetTextShaded(string textArg, textSizes_t size, SDL_Color colour, SDL_Color bgColour, bool wordWrap) {
  _textContents = textArg;

  if(!_lines.empty()) {
    for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
      SDL_FreeSurface(*it);
    }
    _lines.clear();
  }

  TTF_Font* font = NULL;
  if(size == vsmall) {
    font = vSmallFont;
  } else if(size == small) {
    font = smallFont;
  } else if(size == medium) {
    font = mediumFont;
  } else if(size == large) {
    font = largeFont;
  } else {
    font = vLargeFont;
  }

  std::string finalTextContents = textArg;

  if(wordWrap) {
    finalTextContents = DoWordWrap(font, finalTextContents);
  }

  std::list<std::string> lines;
  std::string line;
  for(int i = 0; i < (int)finalTextContents.size(); i++) {
    char c = finalTextContents.at(i);
    if(c=='\n') {
      lines.push_back(line);
      line.clear();
    } else {
      line += c;
    }
  }
  if (!line.empty()) {
    lines.push_back(line);
  }

  for(std::list<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    SDL_Surface* lineSurf = TTF_RenderText_Shaded(font, it->c_str(), colour, bgColour);

    int linePixelWidth;
    int linePixelHeight;
    TTF_SizeText(font, it->c_str(), &linePixelWidth, &linePixelHeight);

    if(linePixelWidth > w) {
      w = linePixelWidth;
    }

    h += linePixelHeight + lineSpacing; 

    _lines.push_back(lineSurf);
  }

  return 1;
}

int Text::SetTextShaded(string textArg, textSizes_t size, Uint8 rF, Uint8 gF, Uint8 bF, Uint8 rB, Uint8 gB, Uint8 bB, bool wordWrap) {
  SDL_Color f = { rF, gF, bF };
  SDL_Color b = { rB, gB, bB };
  return SetTextShaded(textArg, size, f, b, wordWrap);
}

void Text::Render(void) {
  int yOffset = 0;
  for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
    SDL_Surface* lineSurf = *it;
    ApplySurface(x, y + yOffset, lineSurf, screen);  
    yOffset += lineSurf->h + lineSpacing; 
  }
}

void Text::Render(int xArg, int yArg) {
  int yOffset = 0;
  for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
    SDL_Surface* lineSurf = *it;
    ApplySurface(x + xArg, y + yArg + yOffset, lineSurf, screen);  
    yOffset += lineSurf->h + lineSpacing; 
  }
}

void Text::RenderLiteral(void) {
  int yOffset = 0;
  for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
    SDL_Surface* lineSurf = *it;
    ApplySurfaceLiteral(x, y + yOffset, lineSurf, screen);  
    yOffset += lineSurf->h + lineSpacing; 
  }
}

void Text::RenderLiteral(int xArg, int yArg) {
  int yOffset = 0;
  for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
    SDL_Surface* lineSurf = *it;
    ApplySurfaceLiteral(x + xArg, y + yArg + yOffset, lineSurf, screen);  
    yOffset += lineSurf->h + lineSpacing; 
  }
}

std::string Text::DoWordWrap(TTF_Font* fontArg, const std::string& textArg) {
  int leftSpace = lineWidth;

  char* tokenizedText = strdup(textArg.c_str());
  char* tokenizedTextOrigin = tokenizedText;

  std::string wrappedText(textArg);
  int offsetInWrappedText = 0;

  int spaceWidth;
  TTF_SizeText(fontArg, " ", &spaceWidth, NULL);

  char* word = strtok(tokenizedText, " ");

  while (word) {
    int wordWidth;
    TTF_SizeText(fontArg, word, &wordWidth, NULL);

    if ((wordWidth + spaceWidth) > leftSpace) {
      wrappedText.insert((word - tokenizedTextOrigin) + offsetInWrappedText, "\n");
      offsetInWrappedText++;

      leftSpace = lineWidth - wordWidth;
    } else {
      leftSpace -= wordWidth + spaceWidth;
    }

    word = strtok(NULL, " ");
  }

 // delete[] tokenizedText;

  return wrappedText;
}
