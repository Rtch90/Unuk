#ifndef _INGAMEMENU_H_
#define _INGAMEMENU_H_

#include "../Unuk/Globals.h"
#include "../Unuk/Constants.h"
#include "Button.h"
#include "ButtonToggle.h"

enum ingameMenuNavVal_t {
  ingameMenuNothing,
  ingameMenuResume,
  ingameMenuSaveGame,
  ingameMenuLoadGame,
  ingameMenuOptions,
  ingameMenuMainMenu
};

class IngameMenu {
public:
  IngameMenu(void);
  ~IngameMenu(void);

  ingameMenuNavVal_t HandleInput(void);
  void Render(void);

  void SetStatus(bool arg)  { _active = arg; }
  bool GetStatus(void)      { return _active; }

private:
  bool _active;

  Button btnResume;
  Button btnSaveGame;
  Button btnLoadGame;
  Button btnOptions;
  Button btnExitToMenu;
};

#endif
