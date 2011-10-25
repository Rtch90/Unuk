#ifndef _INPUT_H_
#define _INPUT_H_
#include <SDL/SDL.h>

typedef struct mouse_s {
  int dx, dy;
  int oldx, oldy;
  unsigned int buttons;
  unsigned int oldButtons;
} mouse_t;

typedef struct keyboard_s {
  unsigned char *keys;
  unsigned char *oldKeys;
  int keycount;
  int lastChar;
  unsigned int mods;
} keyboard_t;

typedef struct input_s {
  mouse_t mouse;
  keyboard_t keyboard;
} input_t;

  bool CreateInput(void);
  void UpdateInput(void);

  char GetKey(void);

  unsigned int GetX(void);
  unsigned int GetY(void);
  unsigned int GetOldX(void);
  unsigned int GetOldY(void);
  unsigned int GetMods(void);
  bool KeyDown(int index);
  bool KeyStillDown(int index);
  bool KeyUp(int index);
  bool KeyStillUp(int index);
  bool MouseDown(int button);
  bool MouseStillDown(int button);
  bool MouseUp(int button);
  bool MouseStillUp(int button);

  void DestroyInput(void);

#endif
