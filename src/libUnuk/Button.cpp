#include "Button.h"

Button::Button(void) {

}

Button::~Button(void) {

}

void Button::SetOutRGB(Uint8 r, Uint8 g, Uint8 b) {
  button.SetRGB(r, g, b);
  _mouseOutColour.r = r;
  _mouseOutColour.g = g;
  _mouseOutColour.b = b;
}

void Button::SetOutRGB(SDL_Color colour) {
  button.SetRGB(colour);
  _mouseOutColour = colour;
}

void Button::SetOverRGB(Uint8 r, Uint8 g, Uint8 b) {
  _mouseOverColour.r = r;
  _mouseOverColour.g = g;
  _mouseOverColour.b = b;
}

void Button::SetOverRGB(SDL_Color colour) {
  _mouseOverColour = colour;
}

void Button::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
  button.SetXY(x, y);

  _text.SetXY(x + 10, y + 10);
}

void Button::SetTextRGB(Uint8 r, Uint8 g, Uint8 b) {
  _textColour.r = r;
  _textColour.g = g;
  _textColour.b = b;

  _text.SetTextBlended(_text.GetText(), small, _textColour);
}

void Button::SetTextRGB(SDL_Color colour) {
  _textColour = colour;
  _text.SetTextBlended(_text.GetText(), small, colour);
}

void Button::SetText(string textArg) {
  _text.SetTextBlended(textArg, small, _textColour);

  w = _text.GetWidth();
  h = _text.GetHeight();
  button.SetWidthHeight(w + 20, h + 15);
}

bool Button::CheckMouseOver(void) {
  if(event.motion.x > button.GetX() && event.motion.x < button.GetX() + button.GetWidth()) {
    if(event.motion.y > button.GetY() && event.motion.y < button.GetY() + button.GetHeight()) {
      button.SetRGB(_mouseOverColour.r, _mouseOverColour.g, _mouseOverColour.b);
      return true;
    }
  }
  button.SetRGB(_mouseOutColour);
  return false;
}

void Button::Render(void) {
  button.DrawLiteral();
  _text.RenderLiteral();
}

void Button::Render(int xArg, int yArg) {
  button.DrawLiteral(xArg, yArg);
  _text.RenderLiteral(xArg, yArg);
}
