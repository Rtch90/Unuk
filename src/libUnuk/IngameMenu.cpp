#include "IngameMenu.h"

IngameMenu::IngameMenu(void) {
  _active = false;
  _highlightedButton = 0;

  btnResume.SetOutRGB(200, 200, 200);
  btnResume.SetOverRGB(255, 255, 255);
  btnResume.SetTextRGB(0, 0, 0);
  btnResume.SetText("Resume Game");
  btnResume.SetHighlightRGB(255, 128, 0);
  btnResume.SetHighlighted(true);
  btnResume.SetXY(SCREEN_WIDTH / 2 - btnResume.GetWidth() / 2, 50);

  btnSaveGame.SetOutRGB(200, 200, 200);
  btnSaveGame.SetOverRGB(255, 255, 255);
  btnSaveGame.SetTextRGB(0, 0, 0);
  btnSaveGame.SetText("SaveGame");
  btnSaveGame.SetHighlightRGB(255, 128, 0);
  btnSaveGame.SetHighlighted(false);
  btnSaveGame.SetXY(SCREEN_WIDTH / 2 - btnSaveGame.GetWidth() / 2, 100);

  btnLoadGame.SetOutRGB(200, 200, 200);
  btnLoadGame.SetOverRGB(255, 255, 255);
  btnLoadGame.SetTextRGB(0, 0, 0);
  btnLoadGame.SetText("LoadGame");
  btnLoadGame.SetHighlightRGB(255, 128, 0);
  btnLoadGame.SetHighlighted(false);
  btnLoadGame.SetXY(SCREEN_WIDTH / 2 - btnLoadGame.GetWidth() / 2, 150);

  btnOptions.SetOutRGB(200, 200, 200);
  btnOptions.SetOverRGB(255, 255, 255);
  btnOptions.SetTextRGB(0, 0, 0);
  btnOptions.SetText("Options");
  btnOptions.SetHighlightRGB(255, 128, 0);
  btnOptions.SetHighlighted(false);
  btnOptions.SetXY(SCREEN_WIDTH / 2 - btnOptions.GetWidth() / 2, 200);

  btnExitToMenu.SetOutRGB(200, 200, 200);
  btnExitToMenu.SetOverRGB(255, 255, 255);
  btnExitToMenu.SetTextRGB(0, 0, 0);
  btnExitToMenu.SetText("Exit To Main Menu");
  btnExitToMenu.SetHighlightRGB(255, 128, 0);
  btnExitToMenu.SetHighlighted(false);
  btnExitToMenu.SetXY(SCREEN_WIDTH / 2 - btnExitToMenu.GetWidth() / 2, 250);
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
      if(event.key.keysym.sym == SDLK_ESCAPE) {
        return ingameMenuResume;
      } else if(event.key.keysym.sym == SDLK_DOWN) {
        HighlightNewSelection(_highlightedButton + 1);
      } else if(event.key.keysym.sym == SDLK_UP) {
        HighlightNewSelection(_highlightedButton - 1);
      } else if(event.key.keysym.sym == SDLK_RETURN) {
        switch(_highlightedButton) {
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
  btnResume.RenderLiteral();
  btnSaveGame.RenderLiteral();
  btnLoadGame.RenderLiteral();
  btnOptions.RenderLiteral();
  btnExitToMenu.RenderLiteral();
}

void IngameMenu::HighlightNewSelection(int newButton) {
  // Turn of highlight for currently highlighted button
  switch(_highlightedButton) {
    case 0: btnResume.SetHighlighted(false);     break;
    case 1: btnSaveGame.SetHighlighted(false);   break;
    case 2: btnLoadGame.SetHighlighted(false);   break;
    case 3: btnOptions.SetHighlighted(false);    break;
    case 4: btnExitToMenu.SetHighlighted(false); break;
  }
  
  _highlightedButton = newButton;

  // If < 0 then up was pressed when first index was selected
  // If > 0 then down was pressed when last index was selected
  if(_highlightedButton < 0) {
    _highlightedButton = 4;
  } else if(_highlightedButton > 4) {
    _highlightedButton = 0;
  }

  // Highlight new selection
  switch(_highlightedButton) {
    case 0: btnResume.SetHighlighted(true);     break;
    case 1: btnSaveGame.SetHighlighted(true);   break;
    case 2: btnLoadGame.SetHighlighted(true);   break;
    case 3: btnOptions.SetHighlighted(true);    break;
    case 4: btnExitToMenu.SetHighlighted(true); break;
  }
}
