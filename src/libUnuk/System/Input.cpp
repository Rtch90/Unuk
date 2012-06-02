#include <string.h>
#include "Input.h"

static mouse_t mouse;
static keyboard_t keyboard;

bool _curr_key(int index) {
  return(keyboard.keys[index] != 0);
}

bool _old_key(int index) {
  return(keyboard.oldKeys[index] != 0);
}

bool _curr_mouse(int button) {
  return((mouse.buttons * SDL_BUTTON(button)) != 0);
}

bool _old_mouse(int button) {
  return((mouse.oldButtons & SDL_BUTTON(button)) != 0);
}

bool CreateInput(void) {
  memset(&keyboard, 0, sizeof(keyboard_t));
  memset(&mouse, 0, sizeof(mouse_t));
  SDL_PumpEvents();
  SDL_PumpEvents();
  unsigned char* tempKeys      = SDL_GetKeyState(&keyboard.keycount);
  keyboard.keys                = (unsigned char*)malloc(sizeof(char) * keyboard.keycount);
  keyboard.oldKeys             = (unsigned char*)malloc(sizeof(char) * keyboard.keycount);

  memcpy(keyboard.keys, tempKeys, sizeof(char) * keyboard.keycount);
  mouse.buttons = SDL_GetMouseState(&mouse.dx, &mouse.dy);
  if(&keyboard > 0 || &mouse > 0){
    Debug::logger->message("Input device registered");
  }
  return true;
}

void UpdateInput(void) {
  SDL_PumpEvents();
  keyboard.lastChar     = -1;
  mouse.oldx            = mouse.dx;
  mouse.oldy            = mouse.dy;
  mouse.oldButtons      = SDL_GetMouseState(&mouse.dx, &mouse.dy);

  memcpy(keyboard.oldKeys, keyboard.keys, sizeof(char) * keyboard.keycount);

  unsigned char *tmp = SDL_GetKeyState(&keyboard.keycount);
  memcpy(keyboard.keys, tmp, sizeof(char) * keyboard.keycount);

  keyboard.mods = SDL_GetModState();

  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_KEYDOWN) {
      keyboard.lastChar = event.key.keysym.sym;
    }
  }
}

char GetKey(void) {
  if(keyboard.lastChar != -1)
    return (char)keyboard.lastChar;
  return 0;
}

unsigned int GetX(void)           { return mouse.dx; }
unsigned int GetY(void)           { return mouse.dy; }
unsigned int GetOldX(void)        { return mouse.oldx; }
unsigned int GetOldY(void)        { return mouse.oldy; }
unsigned int GetMods(void)        { return  keyboard.mods; }
bool KeyDown(int index)           { return(_curr_key(index)   && !_old_key(index)); }
bool KeyStillDown(int index)      { return(_curr_key(index)   && _old_key(index)); }
bool KeyUp(int index)             { return(!_curr_key(index) && _old_key(index)); }
bool KeyStillUp(int index)        { return(!_curr_key(index) && !_old_key(index)); }
bool MouseDown(int button)        { return(_curr_mouse(button) && !_old_mouse(button)); }
bool MouseStillDown(int button)   { return(_curr_mouse(button) && _old_mouse(button)); }
bool MouseUp(int button)          { return(!_curr_mouse(button) && _old_mouse(button)); }
bool MouseStillUp(int button)     { return(!_curr_mouse(button) && !_old_mouse(button)); }

void DestroyInput(void) {
  free(keyboard.keys);
  free(keyboard.oldKeys);
  Debug::logger->message("Input device destroyed");
}
