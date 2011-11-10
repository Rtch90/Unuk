#include "Text.h"

TTF_Font* Text::verySmallFont   = NULL;
TTF_Font* Text::smallFont       = NULL;
TTF_Font* Text::mediumFont      = NULL;
TTF_Font* Text::largeFont      = NULL;

Text::Text(void) {
  m_text = NULL;
}

Text::~Text(void) {
  assert(m_text != NULL);
  SDL_FreeSurface(m_text);
}

void Text::LoadFonts(void) {
  // Load the fonts if they are not already in memory.
  assert(verySmallFont == NULL);
  assert(smallFont == NULL);
  assert(mediumFont == NULL);
  assert(largeFont == NULL);

  verySmallFont   = Font("../Data/Media/Fonts/Enigma_2.ttf", 16);
  smallFont       = Font("../Data/Media/Fonts/Enigma_2.ttf", 23);
  mediumFont      = Font("../Data/Media/Fonts/Enigma_2.ttf", 27);
  largeFont      = Font("../Data/Media/Fonts/Enigma_2.ttf", 32);
}

void Text::FreeFonts(void) {
  // If the fonts are loaded, then free them.
  assert(verySmallFont != NULL);
  assert(smallFont != NULL);
  assert(mediumFont != NULL);
  assert(largeFont != NULL);

  TTF_CloseFont(verySmallFont);
  TTF_CloseFont(smallFont);
  TTF_CloseFont(mediumFont);
  TTF_CloseFont(largeFont);
}

void Text::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
}

int Text::SetTextBlended(string textArg, string size, SDL_Color colour) {
  m_textContents = textArg;

  if(m_text != NULL) {
    SDL_FreeSurface(m_text);
  }

  if(size == "vsmall") {
    m_text = TTF_RenderText_Blended(verySmallFont, textArg.c_str(), colour);
    return 1;
  }
  else if(size == "small") {
    m_text = TTF_RenderText_Blended(smallFont, textArg.c_str(), colour);
    return 1;
  }
  else if(size == "medium") {
    m_text = TTF_RenderText_Blended(mediumFont, textArg.c_str(), colour);
    return 1;
  }
  else if(size == "large") {
    m_text = TTF_RenderText_Blended(largeFont, textArg.c_str(), colour);
    return 1;
  } else {
    Debug::logger->message("Text::SetTextBlended(): Invalid size argument %s. Defaulted to small.", size.c_str());
    m_text = TTF_RenderText_Blended(smallFont, textArg.c_str(), colour);
    return 0;
  }
}

int Text::SetTextShaded(string textArg, string size, SDL_Color colour, SDL_Color bgColour) {
  m_textContents = textArg;

  if(m_text != NULL) {
    SDL_FreeSurface(m_text);
  }

  if(size == "vsmall") {
    m_text = TTF_RenderText_Shaded(verySmallFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
  else if(size == "small") {
    m_text = TTF_RenderText_Shaded(smallFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
  else if(size == "medium") {
    m_text = TTF_RenderText_Shaded(mediumFont, textArg.c_str(), colour, bgColour);
    return 1;
  }
  else if(size == "large") {
    m_text = TTF_RenderText_Shaded(largeFont, textArg.c_str(), colour, bgColour);
    return 1;
  } else {
    Debug::logger->message("Text::SetTextBlended(): Invalid size argument %s. Defaulted to small.", size.c_str());
    m_text = TTF_RenderText_Shaded(smallFont, textArg.c_str(), colour, bgColour);
    return 0;
  }
}

void Text::Render(void) {
  ApplySurface(x, y, m_text, screen);
}

void Text::RenderLiteral(void) {
  ApplySurfaceLiteral(x, y, m_text, screen);
}
