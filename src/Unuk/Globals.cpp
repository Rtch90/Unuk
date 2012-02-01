#include "Globals.h"

SDL_Surface* screen         = NULL;
SDL_Surface* errorTexture   = NULL;
SDL_Rect camera;
SDL_Event event;

int levelWidth;
int levelHeight;

bool debugEnabled = true;

EventHistory* eventHistory = NULL;

int plrKeyUp;
int plrKeyDown;
int plrKeyeft;
int plrKeyRight;

int plrBtnSpell;
