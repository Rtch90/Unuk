#include "Globals.h"

SDL_Surface* screen         = NULL;
SDL_Surface* errorTexture   = NULL;

SDL_Rect camera;

SDL_Event event;

int levelWidth;
int levelHeight;

bool debugEnabled = false;
