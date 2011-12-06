#ifndef _MAINMENU_H_
#define _MAINMENU_H_
#include "../Unuk/Constants.h"
#include "ParticleEmitter.h"
#include "Menu.h"
#include "Map.h"
#include "Rect.h"

const int MAIN_MENU_NOTHING     = 0;
const int MAIN_MENU_NEW_GAME    = 1;
const int MAIN_MENU_LOAD_GAME   = 2;
const int MAIN_MENU_OPTIONS     = 3;
const int MAIN_MENU_EXIT        = 4;

class MainMenu : public Menu {
public:
  MainMenu(void);
  ~MainMenu(void);

  int HandleInput(void);
  void Render(void);

private:
  Map* m_background;

  Button btnNewGame;
  Button btnLoadGame;
  Button btnOptions;
  Button btnExit;
};

#endif
