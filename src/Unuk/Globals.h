#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include <SDL/SDL.h>

extern SDL_Surface* screen;
extern SDL_Surface* errorTexture;
extern SDL_Rect camera;
extern SDL_Event event;

extern int levelWidth;
extern int levelHeight;

extern bool debugEnabled;


#endif
