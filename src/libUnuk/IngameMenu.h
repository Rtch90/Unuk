#ifndef _INGAMEMENU_H_
#define _INGAMEMENU_H_
#include "Menu.h"

const int INGAME_MENU_NOTHING          = 0;
const int INGAME_MENU_RESUME           = 1;
const int INGAME_MENU_SAVE_GAME        = 2;
const int INGAME_MENU_LOAD_GAME        = 3;
const int INGAME_MENU_OPTIONS          = 4;
const int INGAME_MENU_EXIT_TO_MMENU    = 5;

class IngameMenu : public Menu {
public:
  IngameMenu(void);
  ~IngameMenu(void);

  int HandleInput(void);
  void Render(void);

  void SetStatus(bool arg)  { m_isActive = arg; }
  bool GetStatus(void)      { return m_isActive; }

private:
  bool m_isActive;

  Button btnResume;
  Button btnSaveGame;
  Button btnLoadGame;
  Button btnOptions;
  Button btnExitToMenu;
};

#endif
