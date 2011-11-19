#ifndef _MENU_H_
#define _MENU_H_
#include "../Unuk/Globals.h"
#include "../Unuk/Constants.h"
#include "Button.h"
#include "ButtonToggle.h"

 class Menu {
public:
   Menu(void)  {};
   ~Menu(void) {};

  virtual int HandleInput(void)   = 0;
  virtual void Render(void)       = 0;

protected:

};

#endif
