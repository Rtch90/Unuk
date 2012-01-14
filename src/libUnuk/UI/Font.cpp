#include "Font.h"

TTF_Font* Font(const char* filename, const int size) {
  ifstream font(filename);

  if(font.is_open() == false) {
    Debug::logger->message("Font: %s cannot be found.");
    exit(-1);
  }
  return TTF_OpenFont(filename, size);
}
