#include "ImageLoader.h"

SDL_Surface* LoadImage(const char* filename) {
  SDL_Surface* loadedImage    = NULL;
  SDL_Surface* optimizedImage = NULL;

  // Initialize loadedImage with the file.
  loadedImage = IMG_Load(filename);
  if(loadedImage != NULL) {
    // Then copy the image to a surface for us to blit later.
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
  } else {
    // Tell us what file is mising and do some stuid error texture thing.
    Debug::logger->message("ImageLoader: %s cannot be found!");
    return errorTexture;
  }
}

SDL_Surface* LoadImageAlpha(const char* filename) {
  SDL_Surface* loadedImage    = NULL;
  SDL_Surface* optimizedImage = NULL;

  // Initialize loadedImage with the file.
  loadedImage = IMG_Load(filename);
  if(loadedImage != NULL) {
    // Then copy the image to a surface and give us an alpha channel.
    optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
  } else {
    // Tell us what file is mising and do some stuid error texture thing.
    Debug::logger->message("ImageLoader: %s cannot be found!");
    return errorTexture;
  }
}
