#pragma once

#include "../Unuk/Constants.h"
#include "FPS.h"
#include "ButtonGroup.h"
#include "Map.h"
#include "Rect.h"
#include "Text.h"

enum mainMenuNavVal_t {
  mainMenuNewGame,
  mainMenuLoadGame,
  mainMenuOptions,
  mainMenuExitGame
};

class MainMenu {
public:
  MainMenu(void);
  ~MainMenu(void);

  mainMenuNavVal_t Run(void);

private:
  void Render(void);

  Map _background;

  Text lblMenu;

  ButtonGroup grpMain;

  bool        btnNewGameActive;
  Rect        rectNewGame;
  Text        lblNewGame;
  ButtonGroup grpNewGame;
};
