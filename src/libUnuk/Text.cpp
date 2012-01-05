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

int Text::SetTextBlended(string textArg, textSizes_t size, SDL_Color colour) {
  _textContents = textArg;

  if(!_lines.empty()) {
    for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
      SDL_FreeSurface(*it);
    }
    _lines.clear();
  }
  
  std::list<std::string> lines;
  std::string line;
  for(int i = 0; i < (int)textArg.size(); i++) {
    char c = textArg.at(i);
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
    SDL_Surface* lineSurf = NULL;
    if(size == vsmall) {
      lineSurf = TTF_RenderText_Blended(vSmallFont, textArg.c_str(), colour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(vSmallFont, textArg.c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    else if(size == small) {
      lineSurf = TTF_RenderText_Blended(smallFont, it->c_str(), colour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(smallFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    else if(size == medium) {
      lineSurf = TTF_RenderText_Blended(mediumFont, it->c_str(), colour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(mediumFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    else if(size == large) {
      lineSurf = TTF_RenderText_Blended(largeFont, it->c_str(), colour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(largeFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    } else {
      lineSurf = TTF_RenderText_Blended(vLargeFont, it->c_str(), colour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(vLargeFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    _lines.push_back(lineSurf);
    
  }
  return 1;
}

int Text::SetTextBlended(string textArg, textSizes_t size, Uint8 r, Uint8 g, Uint8 b) {
  SDL_Color f = { r, g, b };
  return SetTextBlended(textArg, size, f);
}

int Text::SetTextShaded(string textArg, textSizes_t size, SDL_Color colour, SDL_Color bgColour) {
  _textContents = textArg;

  if(!_lines.empty()) {
    for(std::list<SDL_Surface*>::iterator it = _lines.begin(); it != _lines.end(); ++it) {
      SDL_FreeSurface(*it);
    }
    _lines.clear();
  }

  std::list<std::string> lines;
  std::string line;
  for(int i = 0; i < (int)textArg.size(); i++) {
    char c = textArg.at(i);
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
    SDL_Surface* lineSurf;
    if(size == vsmall) {
      lineSurf = TTF_RenderText_Shaded(vSmallFont, it->c_str(), colour, bgColour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(vSmallFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    else if(size == small) {
      lineSurf = TTF_RenderText_Shaded(smallFont, it->c_str(), colour, bgColour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(smallFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    else if(size == medium) {
      lineSurf = TTF_RenderText_Shaded(mediumFont, it->c_str(), colour, bgColour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(mediumFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    else if(size == large) {
      lineSurf = TTF_RenderText_Shaded(largeFont, it->c_str(), colour, bgColour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(largeFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    } else {
      lineSurf = TTF_RenderText_Shaded(vLargeFont, it->c_str(), colour, bgColour);
      int linePixelWidth;
      int linePixelHeight;
      TTF_SizeText(vLargeFont, it->c_str(), &linePixelWidth, &linePixelHeight);
      if(linePixelWidth > w) {
        w = linePixelWidth;
      }
      h += linePixelHeight + lineSpacing; 
    }
    _lines.push_back(lineSurf);
  }
  return 1;
}

int Text::SetTextShaded(string textArg, textSizes_t size, Uint8 rF, Uint8 gF, Uint8 bF, Uint8 rB, Uint8 gB, Uint8 bB) {
  SDL_Color f = { rF, gF, bF };
  SDL_Color b = { rB, gB, bB };
  return SetTextShaded(textArg, size, f, b);
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
