#pragma once
#include <SDL/SDL_ttf.h>
#include <fstream>
#include <assert.h>
#include "../System/Debug.h"
using namespace std;

TTF_Font* Font(const char* filename, const int size);
