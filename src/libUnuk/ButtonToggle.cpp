#include "ButtonToggle.h"

void ButtonToggle::SetOverRGB(Uint8 r, Uint8 g, Uint8 b) {
  Button::SetOverRGB(r, g, b);
}

void ButtonToggle::SetOffRGB(Uint8 r, Uint8 g, Uint8 b) {
  ButtonToggle::SetOutRGB(r, g, b);
}

void ButtonToggle::SetOnRGB(Uint8 r, Uint8 g, Uint8 b) {

}
