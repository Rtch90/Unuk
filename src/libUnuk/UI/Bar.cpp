#include "Bar.h"

Bar::Bar(void) {
  x = 0;
  y = 0;
  width = 0;
  height = 0;

  SetProgress(1.0f);
}

void Bar::SetXY(int xArg, int yArg) {
  x = xArg;
  y = yArg;

  _bgRect.SetXY(x, y);
  _fgRect.SetXY(x, y);
}

void Bar::SetWidthHeight(int wArg, int hArg) {
  if(width == wArg && height == hArg) {
    return;
  }

  width = wArg;
  height = hArg;

  _bgRect.SetWidthHeight(width, height);

  SetProgress(_progress);
}

void Bar::SetBackgroundRGB(Uint8 r, Uint8 g, Uint8 b) {
  _bgRect.SetRGB(r, g, b);
}

void Bar::SetBackgroundRGB(SDL_Color colour) {
  _bgRect.SetRGB(colour);
}

void Bar::SetForegroundRGB(Uint8 r, Uint8 g, Uint8 b) {
  _fgRect.SetRGB(r, g, b);
}

void Bar::SetForegroundRGB(SDL_Color colour) {
  _fgRect.SetRGB(colour);
}

void Bar::SetProgress(float progress) {
  _progress = progress;

  _fgRect.SetWidthHeight((int)(progress * width), height);
}

void Bar::Draw(void) {
  _bgRect.Draw();
  _fgRect.Draw();
}

void Bar::Draw(int xArg, int yArg) {
  _bgRect.Draw(xArg, yArg);
  _fgRect.Draw(xArg, yArg);
}

void Bar::DrawLiteral(void) {
  _bgRect.DrawLiteral();
  _fgRect.DrawLiteral();
}

void Bar::DrawLiteral(int xArg, int yArg) {
  _bgRect.DrawLiteral(xArg, yArg);
  _fgRect.DrawLiteral(xArg, yArg);
}
