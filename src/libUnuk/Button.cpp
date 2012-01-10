#include "Button.h"

Button::Button(void) {
  _highlighted = false;
  _mouseOver = false;
}

Button::~Button(void) {

}

void Button::SetOutRGB(Uint8 r, Uint8 g, Uint8 b) {
  _button.SetRGB(r, g, b);
  _mouseOutColour.r = r;
  _mouseOutColour.g = g;
  _mouseOutColour.b = b;
}

void Button::SetOutRGB(SDL_Color colour) {
  _button.SetRGB(colour);
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

void Button::SetHighlightRGB(Uint8 r, Uint8 g, Uint8 b) {
  _highlightColour.r = r;
  _highlightColour.g = g;
  _highlightColour.b = b;
}

void Button::SetHighlightRGB(SDL_Color colour) {
  _highlightColour = colour;
}

void Button::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
  _button.SetXY(x, y);

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
  _button.SetWidthHeight(w + 20, h + 15);
}

bool Button::CheckMouseOver(void) {
  if(event.motion.x > _button.GetX() && event.motion.x < _button.GetX() + _button.GetWidth()) {
    if(event.motion.y > _button.GetY() && event.motion.y < _button.GetY() + _button.GetHeight()) {
      if(_highlighted) {
        _button.SetRGB(_mouseOverColour.r, _mouseOverColour.g, _mouseOverColour.b);
      }
      return true;
    }
  }
  if(!_highlighted) {
    _button.SetRGB(_mouseOutColour);
  }
  return false;
}

void Button::SetHighlighted(bool highlighted) { 
  if(_highlighted != highlighted) {
    if(highlighted) {
      _button.SetRGB(_highlightColour);
    } else {
      if(_mouseOver) {
        _button.SetRGB(_mouseOverColour);
      } else {
        _button.SetRGB(_textColour);
      }
    }
  }
  _highlighted = highlighted;
}

void Button::Render(void) {
  _button.Draw();
  _text.Render();
}

void Button::Render(int xArg, int yArg) {
  _button.Draw(xArg, yArg);
  _text.Render(xArg, yArg);
}

void Button::RenderLiteral(void) {
  _button.DrawLiteral();
  _text.RenderLiteral();
}

void Button::RenderLiteral(int xArg, int yArg) {
  _button.DrawLiteral(xArg, yArg);
  _text.RenderLiteral(xArg, yArg);
}
