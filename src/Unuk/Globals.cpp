#include "Globals.h"

SDL_Surface* screen         = NULL;
SDL_Surface* errorTexture   = NULL;
SDL_Rect camera;
SDL_Event event;

// Start off false. press 'p' to turn it on!
bool debugEnabled = false;

EventHistory* eventHistory = NULL;

int plrKeyUp;
int plrKeyDown;
int plrKeyeft;
int plrKeyRight;

int plrBtnSpell;

bool gameOver = false;
