#include "Button.h"

Button::Button(void) {

}

Button::~Button(void) {

}

void Button::SetOutRGB(Uint8 r, Uint8 g, Uint8 b) {
  button.SetRGB(r, g, b);
  m_mouseOutColour.r = r;
  m_mouseOutColour.g = g;
  m_mouseOutColour.b = b;
}

void Button::SetOutRGB(SDL_Color colour) {
  button.SetRGB(colour);
  m_mouseOutColour = colour;
}

void Button::SetOverRGB(Uint8 r, Uint8 g, Uint8 b) {
  m_mouseOverColour.r = r;
  m_mouseOverColour.g = g;
  m_mouseOverColour.b = b;
}

void Button::SetOverRGB(SDL_Color colour) {
  m_mouseOverColour = colour;
}

void Button::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;
  button.SetXY(x, y);

  m_text.SetXY(x + 10, y + 10);
}

void Button::SetTextRGB(Uint8 r, Uint8 g, Uint8 b) {
  m_textColour.r = r;
  m_textColour.g = g;
  m_textColour.b = b;

  m_text.SetTextBlended(m_text.GetText(), "small", m_textColour);
}

void Button::SetTextRGB(SDL_Color colour) {
  m_textColour = colour;
  m_text.SetTextBlended(m_text.GetText(), "small", colour);
}

void Button::SetText(string textArg) {
  m_text.SetTextBlended(textArg, "small", m_textColour);

  w = m_text.GetWidth();
  h = m_text.GetHeight();
  button.SetWidthHeight(w + 20, h + 15);
}

bool Button::CheckMouseOver(void) {
  if(event.motion.x > button.GetX() && event.motion.x < button.GetX() + button.GetWidth()) {
    if(event.motion.y > button.GetY() && event.motion.y < button.GetY() + button.GetHeight()) {
      button.SetRGB(m_mouseOverColour.r, m_mouseOverColour.g, m_mouseOverColour.b);
      return true;
    }
  }
  button.SetRGB(m_mouseOutColour);
  return false;
}

void Button::Render(void) {
  button.DrawLiteral();
  m_text.RenderLiteral();
}

void Button::Render(int xArg, int yArg) {
  button.DrawLiteral(xArg, yArg);
  m_text.RenderLiteral(xArg, yArg);
}
