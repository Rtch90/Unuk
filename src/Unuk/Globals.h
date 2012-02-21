#pragma once
#include <SDL/SDL.h>

extern SDL_Surface* screen;
extern SDL_Surface* errorTexture;
extern SDL_Rect camera;
extern SDL_Event event;

extern bool debugEnabled;

class EventHistory;

extern EventHistory* eventHistory;

extern bool gameOver;
