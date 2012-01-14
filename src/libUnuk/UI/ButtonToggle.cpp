#include "ButtonToggle.h"

ButtonToggle::ButtonToggle(void) {

}

ButtonToggle::~ButtonToggle(void) {

}

void ButtonToggle::SetOverRGB(Uint8 r, Uint8 g, Uint8 b) {
  Button::SetOverRGB(r, g, b);
}

void ButtonToggle::SetOverRGB(SDL_Color colour) {
  Button::SetOverRGB(colour);
}

void ButtonToggle::SetOffRGB(Uint8 r, Uint8 g, Uint8 b) {
  ButtonToggle::SetOutRGB(r, g, b);
}

void ButtonToggle::SetOffRGB(SDL_Color colour) {
  Button::SetOutRGB(colour);
}

void ButtonToggle::SetOnRGB(Uint8 r, Uint8 g, Uint8 b) {
  _onColour.r = r;
  _onColour.g = g;
  _onColour.b = b;
}

void ButtonToggle::SetOnRGB(SDL_Color colour) {
  _onColour = colour;
}
