#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../Unuk/Globals.h"
#include "../System/Debug.h"

SDL_Surface* LoadImage(const char* filename);
SDL_Surface* LoadImageAlpha(const char* filename);
