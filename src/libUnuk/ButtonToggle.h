#ifndef _BUTTONTOGGLE_H_
#define _BUTTONTOGGLE_H_
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Button.h"

class ButtonToggle : protected Button {
public:
  ButtonToggle(void);
  ~ButtonToggle(void);

  void SetOverRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetOverRGB(SDL_Color);
  void SetOffRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetOffRGB(SDL_Color);
  void SetOnRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetOnRGB(SDL_Color);

  void SetTextRGB(Uint8 r, Uint8 g, Uint8 b);
  void SetOnText(string);
  void SetOffText(string);

  void SetState(bool);
  bool GetState(void) { return m_state; }

  bool CheckMouseOver(void);

  void Render(void);

private:
  bool m_state;

  SDL_Colour m_onColour;

  Text m_onText;
};


#endif
