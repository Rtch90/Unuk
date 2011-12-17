#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <iostream>

#include "../libUnuk/MainMenu.h"
#include "../libUnuk/NPC.h"
#include "../libUnuk/Debug.h"
#include "Constants.h"
#include "Globals.h"
#include "Game.h"

int main() {
  if(SDL_Init(SDL_INIT_VIDEO == -1)) {
    system("zenity --error --text=\"Could not load SDL\"");
    Debug::logger->message("Error: Could not load SDL");
    return 1;
  }
  if(TTF_Init() == -1) {
    system("zenity --error --text=\"Could not load SDL_TTF\"");
    Debug::logger->message("Error: Could not load SDL_TTF");
    return 1;
  }

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("fps - 00", NULL);

  srand(time(NULL));

  camera.x = 0;
  camera.y = 0;
  camera.w = SCREEN_WIDTH;
  camera.h = SCREEN_HEIGHT;

  errorTexture = LoadImage("../Data/Media/error.png");

  Text::LoadFonts();

  Game* game = NULL;
  MainMenu* menu = new MainMenu;

  bool menuRunning = true;
  while(menuRunning) {
    switch(menu->Run()) {
    case mainMenuNewGame:
      delete menu;
      game = new Game;

      switch(game->Run("save")) {
      case gameMainMenu:
        menu = new MainMenu;
        break;
      case gameQuitGame:
        menuRunning = false;
        break;
      }

      delete game;
      break;
    case mainMenuLoadGame:
      break;
    case mainMenuOptions:
      break;
    case mainMenuExitGame:
      menuRunning = false;
      delete menu;
      break;
    }
  }
  //stringstream caption;
  //caption << "Unuk - FPS: " << fps;

  //SDL_WM_SetCaption(caption.str().c_str(), NULL);

  // Clean up after ourselves.
  Text::FreeFonts();

  SDL_FreeSurface(screen);
  SDL_FreeSurface(errorTexture);

  SDL_Quit();
  TTF_Quit();

  return 0;
}
