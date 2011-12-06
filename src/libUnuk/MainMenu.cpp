#include "MainMenu.h"

MainMenu::MainMenu(void) {
  btnNewGame.SetOutRGB(200, 200, 200);
  btnNewGame.SetOverRGB(255, 255, 255);
  btnNewGame.SetTextRGB(0, 0, 0);
  btnNewGame.SetText("New Game");
  btnNewGame.SetXY(100, 100);

  btnLoadGame.SetOutRGB(200, 200, 200);
  btnLoadGame.SetOverRGB(255, 255, 255);
  btnLoadGame.SetTextRGB(0, 0, 0);
  btnLoadGame.SetText("Load Game");
  btnLoadGame.SetXY(100, 150);

  btnOptions.SetOutRGB(200, 200, 200);
  btnOptions.SetOverRGB(255, 255, 255);
  btnOptions.SetTextRGB(0, 0, 0);
  btnOptions.SetText("Options");
  btnOptions.SetXY(100, 200);

  btnExit.SetOutRGB(200, 200, 200);
  btnExit.SetOverRGB(255, 255, 255);
  btnExit.SetTextRGB(0, 0, 0);
  btnExit.SetText("Exit");
  btnExit.SetXY(100, 250);
  m_background = new Map;
  m_background->Load("MainMenu");
  camera.x = 0;
  camera.y = 0;
}

MainMenu::~MainMenu(void) {
  delete m_background;
}

int MainMenu::HandleInput(void) {
  while(SDL_PollEvent(&event)) {
    btnNewGame.CheckMouseOver();
    btnLoadGame.CheckMouseOver();
    btnOptions.CheckMouseOver();
    btnExit.CheckMouseOver();

    if(event.type == SDL_MOUSEBUTTONUP) {
      if(event.button.button == SDL_BUTTON_LEFT) {
        if(btnNewGame.CheckMouseOver())
          return MAIN_MENU_NEW_GAME;
        else if(btnLoadGame.CheckMouseOver())
          return MAIN_MENU_LOAD_GAME;
        else if(btnOptions.CheckMouseOver())
          return MAIN_MENU_OPTIONS;
        else if(btnExit.CheckMouseOver())
          return MAIN_MENU_EXIT;
      }
    }
    else if(event.type == SDL_QUIT) {
      return MAIN_MENU_EXIT;
    }
  }
  return MAIN_MENU_NOTHING;
}

void MainMenu::Render(void) {
  m_background->Render();

  btnNewGame.Render();
  btnLoadGame.Render();
  btnOptions.Render();
  btnExit.Render();
}
