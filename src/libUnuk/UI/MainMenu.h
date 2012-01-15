#pragma once

#include "../../Unuk/Constants.h"
#include "../System/FPS.h"
#include "../UI/ButtonGroup.h"
#include "../LevelGen/LevelGen.h"
#include "../System/Rect.h"
#include "../UI/Text.h"

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

	LevelGen _background;

  Text lblMenu;

  ButtonGroup grpMain;

  bool        btnNewGameActive;
  Rect        rectNewGame;
  Text        lblNewGame;
  ButtonGroup grpNewGame;
};
