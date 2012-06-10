#include "IngameMenu.h"
#include "../Engine/MemManager.h"

IngameMenu::IngameMenu(void) {
  _active = false;

  Button* btnResume = scNew(Button,);
  btnResume->SetOutRGB(200, 200, 200);
  btnResume->SetOverRGB(255, 255, 255);
  btnResume->SetTextRGB(0, 0, 0);
  btnResume->SetText("Resume Game");
  btnResume->SetHighlightRGB(255, 128, 0);
  btnResume->SetHighlighted(false);
  btnResume->SetXY(SCREEN_WIDTH / 2 - btnResume->GetWidth() / 2, 50);

  Button* btnSaveGame = scNew(Button,);
  btnSaveGame->SetOutRGB(200, 200, 200);
  btnSaveGame->SetOverRGB(255, 255, 255);
  btnSaveGame->SetTextRGB(0, 0, 0);
  btnSaveGame->SetText("SaveGame");
  btnSaveGame->SetHighlightRGB(255, 128, 0);
  btnSaveGame->SetHighlighted(false);
  btnSaveGame->SetXY(SCREEN_WIDTH / 2 - btnSaveGame->GetWidth() / 2, 100);

  Button* btnLoadGame = scNew(Button,);
  btnLoadGame->SetOutRGB(200, 200, 200);
  btnLoadGame->SetOverRGB(255, 255, 255);
  btnLoadGame->SetTextRGB(0, 0, 0);
  btnLoadGame->SetText("LoadGame");
  btnLoadGame->SetHighlightRGB(255, 128, 0);
  btnLoadGame->SetHighlighted(false);
  btnLoadGame->SetXY(SCREEN_WIDTH / 2 - btnLoadGame->GetWidth() / 2, 150);

  Button* btnOptions = scNew(Button,);
  btnOptions->SetOutRGB(200, 200, 200);
  btnOptions->SetOverRGB(255, 255, 255);
  btnOptions->SetTextRGB(0, 0, 0);
  btnOptions->SetText("Options");
  btnOptions->SetHighlightRGB(255, 128, 0);
  btnOptions->SetHighlighted(false);
  btnOptions->SetXY(SCREEN_WIDTH / 2 - btnOptions->GetWidth() / 2, 200);

  Button* btnExitToMenu = scNew(Button,);
  btnExitToMenu->SetOutRGB(200, 200, 200);
  btnExitToMenu->SetOverRGB(255, 255, 255);
  btnExitToMenu->SetTextRGB(0, 0, 0);
  btnExitToMenu->SetText("Exit To Main Menu");
  btnExitToMenu->SetHighlightRGB(255, 128, 0);
  btnExitToMenu->SetHighlighted(false);
  btnExitToMenu->SetXY(SCREEN_WIDTH / 2 - btnExitToMenu->GetWidth() / 2, 250);

  _buttons.AddButton(btnResume);
  _buttons.AddButton(btnSaveGame);
  _buttons.AddButton(btnLoadGame);
  _buttons.AddButton(btnOptions);
  _buttons.AddButton(btnExitToMenu);
}

IngameMenu::~IngameMenu(void) {
}

ingameMenuNavVal_t IngameMenu::HandleInput(void) {
  while(SDL_PollEvent(&event)) {
    _buttons.CheckMouseOverDummy();

    if(event.key.type == SDL_KEYDOWN) {
      if(event.key.keysym.sym == SDLK_ESCAPE) {
        return ingameMenuResume;
      } else if(event.key.keysym.sym == SDLK_DOWN) {
        _buttons.SelectNext();
      } else if(event.key.keysym.sym == SDLK_UP) {
        _buttons.SelectPrevious();
      } else if(event.key.keysym.sym == SDLK_RETURN) {
        switch(_buttons.GetSelectedButton()) {
        case 0: return ingameMenuResume;
        case 1: return ingameMenuSaveGame;
        case 2: return ingameMenuLoadGame;
        case 3: return ingameMenuOptions;
        case 4: return ingameMenuMainMenu;
        }
      }
    }
    else if(event.type == SDL_MOUSEBUTTONUP) {
      if(event.button.button == SDL_BUTTON_LEFT) {
        switch(_buttons.CheckMouseOver()) {
        case 0: return ingameMenuResume;
        case 1: return ingameMenuSaveGame;
        case 2: return ingameMenuLoadGame;
        case 3: return ingameMenuOptions;
        case 4: return ingameMenuMainMenu;
        }
      }
    }
  }
  return ingameMenuNothing;
}

void IngameMenu::Render(void) {
  _buttons.RenderLiteral();
}
