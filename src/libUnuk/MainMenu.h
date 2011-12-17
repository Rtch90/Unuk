#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "../Unuk/Constants.h"
#include "FPS.h"
#include "Button.h"
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
  void Render(void);

private:
  Map _background;

  Text lblMenu;

  Button btnNewGame;

  bool    btnNewGameActive;
  Rect    rectNewGame;
  Text    lblNewGame;
  Button  btnNewGameYes;
  Button  btnNewGameNo;

  Button btnLoadGame;
  Button btnOptions;
  Button btnExit;
};

#endif
