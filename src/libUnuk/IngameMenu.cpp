#include "IngameMenu.h"

IngameMenu::IngameMenu(void) {
  _active = false;

  btnResume.SetOutRGB(200, 200, 200);
  btnResume.SetOverRGB(255, 255, 255);
  btnResume.SetTextRGB(0, 0, 0);
  btnResume.SetText("Resume Game");
  btnResume.SetXY((SCREEN_WIDTH / 2) - (btnResume.GetWidth() / 2), 50);

  btnSaveGame.SetOutRGB(200, 200, 200);
  btnSaveGame.SetOverRGB(255, 255, 255);
  btnSaveGame.SetTextRGB(0, 0, 0);
  btnSaveGame.SetText("SaveGame");
  btnSaveGame.SetXY((SCREEN_WIDTH / 2) - (btnSaveGame.GetWidth() / 2), 100);

  btnLoadGame.SetOutRGB(200, 200, 200);
  btnLoadGame.SetOverRGB(255, 255, 255);
  btnLoadGame.SetTextRGB(0, 0, 0);
  btnLoadGame.SetText("LoadGame");
  btnLoadGame.SetXY((SCREEN_WIDTH / 2) - (btnLoadGame.GetWidth() / 2), 150);

  btnOptions.SetOutRGB(200, 200, 200);
  btnOptions.SetOverRGB(255, 255, 255);
  btnOptions.SetTextRGB(0, 0, 0);
  btnOptions.SetText("Options");
  btnOptions.SetXY((SCREEN_WIDTH / 2) - (btnOptions.GetWidth() / 2), 200);

  btnExitToMenu.SetOutRGB(200, 200, 200);
  btnExitToMenu.SetOverRGB(255, 255, 255);
  btnExitToMenu.SetTextRGB(0, 0, 0);
  btnExitToMenu.SetText("Exit To Main Menu");
  btnExitToMenu.SetXY((SCREEN_WIDTH / 2) - (btnExitToMenu.GetWidth() / 2), 250);
}

IngameMenu::~IngameMenu(void) {

}

ingameMenuNavVal_t IngameMenu::HandleInput(void) {
  while(SDL_PollEvent(&event)) {
    btnResume.CheckMouseOver();
    btnSaveGame.CheckMouseOver();
    btnLoadGame.CheckMouseOver();
    btnOptions.CheckMouseOver();
    btnExitToMenu.CheckMouseOver();

    if(event.key.type == SDL_KEYDOWN) {
      if(event.key.keysym.sym == SDLK_ESCAPE)
        return ingameMenuResume;
    }
    else if(event.type == SDL_MOUSEBUTTONUP) {
      if(event.button.button == SDL_BUTTON_LEFT) {
        if(btnResume.CheckMouseOver())
          return ingameMenuResume;
        else if(btnSaveGame.CheckMouseOver())
          return ingameMenuSaveGame;
        else if(btnLoadGame.CheckMouseOver())
          return ingameMenuLoadGame;
        else if(btnOptions.CheckMouseOver())
          return ingameMenuOptions;
        else if(btnExitToMenu.CheckMouseOver())
          return ingameMenuMainMenu;
      }
    }
  }
  return ingameMenuNothing;
}

void IngameMenu::Render(void) {
  btnResume.Render();
  btnSaveGame.Render();
  btnLoadGame.Render();
  btnOptions.Render();
  btnExitToMenu.Render();
}
