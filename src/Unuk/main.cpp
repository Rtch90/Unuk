#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <iostream>

#include "../libUnuk/Ui/MainMenu.h"
#include "../libUnuk/Engine/NPC.h"
#include "../libUnuk/System/Debug.h"
#include "../libUnuk/Engine/MemClass.h"
#include "Constants.h"
#include "Globals.h"
#include "Game.h"

// The following is needed to avoid linking SDLmain.lib and prevent
// a name clash with LoadImage from the Win32 API.
#if defined(_WIN32)
#include <Windows.h>
#if defined(main)
#undef main
#endif
#if defined(LoadImage)
#undef LoadImage
#endif
#endif

#if !defined(_WIN32) || defined(_DEBUG)
int main() {
#else
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
#endif

  Debug::openLog(true);
  Debug::logger->message("\n----- Engine Loading -----");

  if(SDL_Init(SDL_INIT_VIDEO == -1)) {
    system("zenity --error --text=\"Could not load SDL\"");
    Debug::logger->message("Error: Could not load SDL");
    return 1;
  } else
    Debug::logger->message("SDL loaded..");

  if(TTF_Init() == -1) {
    system("zenity --error --text=\"Could not load SDL_TTF\"");
    Debug::logger->message("Error: Could not load SDL_TTF");
    return 1;
  } else
    Debug::logger->message("SDL_TTF loaded..");



  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
  Debug::logger->message("Video mode set..");

  SDL_WM_SetCaption("fps - 00", NULL);

  srand((unsigned int)time(NULL));

  camera.x = 0;
  camera.y = 0;
  camera.w = SCREEN_WIDTH;
  camera.h = SCREEN_HEIGHT;

  errorTexture = LoadImage("../Data/Media/error.png");

  Text::LoadFonts();

  Game* game = NULL;

  Debug::logger->message("Creating mainmenu..");
  MainMenu* menu = new MainMenu;

  Debug::logger->message("\n----- Engine Initialization Complete -----");
  Debug::logger->message("\n----- Logic -----");

  bool menuRunning = true;
  while(menuRunning) {
    switch(menu->Run()) {
    case mainMenuNewGame:
      delete menu;
      Debug::logger->message("Entering game state..");
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
