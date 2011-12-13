#include "MainMenu.h"

MainMenu::MainMenu(void) {
  btnNewGame.SetOutRGB(200, 200, 200);
  btnNewGame.SetOverRGB(255, 255, 255);
  btnNewGame.SetTextRGB(0, 0, 0);
  btnNewGame.SetText("New Game");
  btnNewGame.SetXY(100, 150);

  btnNewGameActive = false;

  lblNewGame.SetXY(275, 160);
  lblNewGame.SetTextBlended("This will delete your current game, are you sure?", "vsmall", 0, 0, 0);

  rectNewGame.SetRGB(200, 200, 200);
  rectNewGame.SetXY(250, 150);
  rectNewGame.SetWidthHeight(lblNewGame.GetWidth() + 50, 90);

  btnNewGameYes.SetOutRGB(20, 150, 20);
  btnNewGameYes.SetOverRGB(20, 255, 20);
  btnNewGameYes.SetTextRGB(0, 0, 0);
  btnNewGameYes.SetText("Yes");
  btnNewGameYes.SetXY(rectNewGame.GetX() + rectNewGame.GetWidth() / 2 - 40 - btnNewGameYes.GetWidth(), 190);

  btnNewGameNo.SetOutRGB(150, 20, 20);
  btnNewGameNo.SetOverRGB(255, 20, 20);
  btnNewGameNo.SetTextRGB(0, 0, 0);
  btnNewGameNo.SetText("No");
  btnNewGameNo.SetXY(rectNewGame.GetX() + rectNewGame.GetWidth() / 2 + 40 - btnNewGameNo.GetWidth(), 190);

  btnLoadGame.SetOutRGB(200, 200, 200);
  btnLoadGame.SetOverRGB(255, 255, 255);
  btnLoadGame.SetTextRGB(0, 0, 0);
  btnLoadGame.SetText("Load Game");
  btnLoadGame.SetXY(100, 200);

  btnOptions.SetOutRGB(200, 200, 200);
  btnOptions.SetOverRGB(255, 255, 255);
  btnOptions.SetTextRGB(0, 0, 0);
  btnOptions.SetText("Options");
  btnOptions.SetXY(100, 250);

  btnExit.SetOutRGB(200, 200, 200);
  btnExit.SetOverRGB(255, 255, 255);
  btnExit.SetTextRGB(0, 0, 0);
  btnExit.SetText("Exit");
  btnExit.SetXY(100, 300);

  lblMenu.SetXY(100, 75);
  lblMenu.SetTextBlended("Unuk", "vlarge", 0, 0, 0);

  m_background.Load("MainMenu");

  camera.x = 0;
  camera.y = 0;
}

MainMenu::~MainMenu(void) {

}

int MainMenu::HandleInput(void) {
  while(SDL_PollEvent(&event)) {
    btnNewGame.CheckMouseOver();
    if(btnNewGameActive) {
      btnNewGameYes.CheckMouseOver();
      btnNewGameNo.CheckMouseOver();
    }

    btnLoadGame.CheckMouseOver();
    btnOptions.CheckMouseOver();
    btnExit.CheckMouseOver();

    if(event.type == SDL_MOUSEBUTTONUP) {
      if(event.button.button == SDL_BUTTON_LEFT) {
        if(btnNewGame.CheckMouseOver())
          btnNewGameActive = !btnNewGameActive;
        else if(btnLoadGame.CheckMouseOver())
          return MAIN_MENU_LOAD_GAME;
        else if(btnOptions.CheckMouseOver())
          return MAIN_MENU_OPTIONS;
        else if(btnExit.CheckMouseOver())
          return MAIN_MENU_EXIT;

        if(btnNewGameActive) {
          if(btnNewGameYes.CheckMouseOver())
            return MAIN_MENU_NEW_GAME;
          else if(btnNewGameNo.CheckMouseOver())
            btnNewGameActive = false;
        }
      }
    }
    else if(event.type == SDL_QUIT) {
      return MAIN_MENU_EXIT;
    }
  }
  return MAIN_MENU_NOTHING;
}

void MainMenu::Render(void) {
  m_background.Render();

  lblMenu.Render();

  btnNewGame.Render();
  if(btnNewGameActive) {
    rectNewGame.Draw();
    lblNewGame.Render();
    btnNewGameYes.Render();
    btnNewGameNo.Render();
  }

  btnLoadGame.Render();
  btnOptions.Render();
  btnExit.Render();
}
