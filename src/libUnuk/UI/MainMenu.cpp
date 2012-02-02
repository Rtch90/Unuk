#include "MainMenu.h"

MainMenu::MainMenu(void) {
  Button* btnNewGame = new Button();
  btnNewGame->SetOutRGB(200, 200, 200);
  btnNewGame->SetOverRGB(255, 255, 255);
  btnNewGame->SetTextRGB(0, 0, 0);
  btnNewGame->SetText("New Game");
  btnNewGame->SetXY(100, 150);
  btnNewGame->SetHighlightRGB(255, 128, 0);
  btnNewGame->SetHighlighted(false);

  Button* btnLoadGame = new Button();
  btnLoadGame->SetOutRGB(200, 200, 200);
  btnLoadGame->SetOverRGB(255, 255, 255);
  btnLoadGame->SetTextRGB(0, 0, 0);
  btnLoadGame->SetText("Load Game");
  btnLoadGame->SetHighlightRGB(255, 128, 0);
  btnLoadGame->SetHighlighted(false);
  btnLoadGame->SetXY(100, 200);

  Button* btnOptions = new Button();
  btnOptions->SetOutRGB(200, 200, 200);
  btnOptions->SetOverRGB(255, 255, 255);
  btnOptions->SetTextRGB(0, 0, 0);
  btnOptions->SetText("Options");
  btnOptions->SetHighlightRGB(255, 128, 0);
  btnOptions->SetHighlighted(false);
  btnOptions->SetXY(100, 250);

  Button* btnExit = new Button();
  btnExit->SetOutRGB(200, 200, 200);
  btnExit->SetOverRGB(255, 255, 255);
  btnExit->SetTextRGB(0, 0, 0);
  btnExit->SetText("Exit");
  btnExit->SetHighlightRGB(255, 128, 0);
  btnExit->SetHighlighted(false);
  btnExit->SetXY(100, 300);  

  grpMain.AddButton(btnNewGame);
  grpMain.AddButton(btnLoadGame);
  grpMain.AddButton(btnOptions);
  grpMain.AddButton(btnExit);

  btnNewGameActive = false;

  lblNewGame.SetXY(275, 160);
  lblNewGame.SetTextBlended("This will delete your current game, are you sure?", vsmall, 0, 0, 0);

  rectNewGame.SetRGB(200, 200, 200);
  rectNewGame.SetXY(250, 150);
  rectNewGame.SetWidthHeight(lblNewGame.GetWidth() + 50, 90);

  lblMenu.SetXY(100, 75);
  lblMenu.SetTextBlended("Unuk", vlarge, 0, 0, 0);

  Button* btnNewGameYes = new Button();
  btnNewGameYes->SetOutRGB(20, 150, 20);
  btnNewGameYes->SetOverRGB(20, 255, 20);
  btnNewGameYes->SetTextRGB(0, 0, 0);
  btnNewGameYes->SetText("Yes");
  btnNewGameYes->SetHighlightRGB(255, 128, 0);
  btnNewGameYes->SetHighlighted(false);
  btnNewGameYes->SetXY(rectNewGame.GetX() + rectNewGame.GetWidth() / 2 - 40 - btnNewGameYes->GetWidth(), 190);

  Button* btnNewGameNo = new Button();
  btnNewGameNo->SetOutRGB(150, 20, 20);
  btnNewGameNo->SetOverRGB(255, 20, 20);
  btnNewGameNo->SetTextRGB(0, 0, 0);
  btnNewGameNo->SetText("No");
  btnNewGameNo->SetHighlightRGB(255, 128, 0);
  btnNewGameNo->SetHighlighted(false);
  btnNewGameNo->SetXY(rectNewGame.GetX() + rectNewGame.GetWidth() / 2 + 40 - btnNewGameNo->GetWidth(), 190);

  grpNewGame.AddButton(btnNewGameYes);
  grpNewGame.AddButton(btnNewGameNo);

  //m_background.Load("MainMenu");

  camera.x = 0;
  camera.y = 0;
}

MainMenu::~MainMenu(void) {

}

mainMenuNavVal_t MainMenu::Run(void) {
  FPS fpsLimiter(20);

  bool running = true;
  while(running) {
    Render();
    SDL_Flip(screen);

    while(SDL_PollEvent(&event)) {
      grpMain.CheckMouseOverDummy();

      if(btnNewGameActive) {
        grpNewGame.CheckMouseOverDummy();
      }

      if(event.key.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_DOWN) {
          if(btnNewGameActive) {
            grpNewGame.SelectNext();
          } else {
            grpMain.SelectNext();
          }
        } else if(event.key.keysym.sym == SDLK_UP) {
          if(btnNewGameActive) {
            grpNewGame.SelectPrevious();
          } else {
            grpMain.SelectPrevious();
          }
        } else if(event.key.keysym.sym == SDLK_RETURN) {
          if(btnNewGameActive) {
            switch(grpNewGame.GetSelectedButton()) {
              case 0: return mainMenuNewGame; break;
              case 1: btnNewGameActive = false; break;
            }
          } else {
            switch(grpMain.GetSelectedButton()) {
              case 0: btnNewGameActive = !btnNewGameActive; break;
              case 1: return mainMenuLoadGame;
              case 2: return mainMenuOptions;
              case 3: return mainMenuExitGame;
            }
          }
        } else if(event.key.keysym.sym == SDLK_ESCAPE) {
          return mainMenuExitGame;
        }
      }
      else if(event.type == SDL_MOUSEBUTTONUP) {
        if(event.button.button == SDL_BUTTON_LEFT) {
          switch(grpMain.CheckMouseOver()) {
            case 0: btnNewGameActive = !btnNewGameActive; break;
            case 1: return mainMenuLoadGame;
            case 2: return mainMenuOptions;
            case 3: return mainMenuExitGame;
          }

          if(btnNewGameActive) {
            switch(grpNewGame.CheckMouseOver()) {
              case 0: return mainMenuNewGame; break;
              case 1: btnNewGameActive = false; break;
            }
          }
        }
      }
      else if(event.type == SDL_QUIT) {
        return mainMenuExitGame;
      }
    }

    fpsLimiter.LimitFPS();
  }
  return mainMenuExitGame;
}

void MainMenu::Render(void) {
  //m_background.Render();

  lblMenu.Render();

  grpMain.RenderLiteral();

  if(btnNewGameActive) {
    rectNewGame.Draw();
    lblNewGame.Render();
    grpNewGame.RenderLiteral();
  }
}
