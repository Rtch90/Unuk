#pragma once

#include "../../Unuk/Globals.h"
#include "../../Unuk/Constants.h"
#include "ButtonGroup.h"
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

  ButtonGroup _buttons;
};
