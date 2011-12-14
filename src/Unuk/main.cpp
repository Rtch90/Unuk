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

  int fps;
  int frame;
  const int MAX_FPS = 20;

  Timer frameTimer;
  frameTimer.Start();

  Timer fpsCalc;
  fpsCalc.Start();

  bool menuRunning = true;
  while(menuRunning) {
    menu->Render();
    SDL_Flip(screen);

    switch(menu->HandleInput()) {
    case mainMenuNothing:
      break;
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
    // Calculate and display the FPS.
    if(fpsCalc.GetTicks() >= 1000) {
      fps = frame / (fpsCalc.GetTicks() / 1000);

      stringstream caption;
      caption << "Unuk: fps - " << fps;

      SDL_WM_SetCaption(caption.str().c_str(), NULL);

      fpsCalc.Start();
      frame = 0;
    }
    // Restrict the FPS.
    if(1000 / MAX_FPS > frameTimer.GetTicks()) {
      // SDL_Delay does not accept a float, so for higher
      // framerate limits there is an innacuracy. This is
      // as much as 3FPS at a limit of 60FPS.
      SDL_Delay((1000 / MAX_FPS) - frameTimer.GetTicks());
    }
    frameTimer.Start();
    frame++;
  }
  // Clean up after ourselves.
  Text::FreeFonts();

  SDL_FreeSurface(screen);
  SDL_FreeSurface(errorTexture);

  SDL_Quit();
  TTF_Quit();

  return 0;
}
