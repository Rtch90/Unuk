#ifndef _KEYBOARDINTERFACE_H_
#define _KEYBOARDINTERFACE_H_

enum UnukKeyCode {
  U_INVALID,
  U_UP,
  U_DOWN,
  U_LEFT,
  U_RIGHT,
  U_SPACE,
  U_w,
  U_a,
  U_s,
  U_d,
  U_MAX_KEYS
};

class KeyboardInterface {
public:
  virtual ~KeyboardInterface(void) {}
  virtual bool IsKeyPressed(UnukKeyCode code)  = 0;
  virtual bool IsKeyHeldDown(UnukKeyCode code) = 0;

  virtual void HandleKeyDown(UnukKeyCode code) = 0;
  virtual void HandleKeyUp(UnukKeyCode code)   = 0;
  // Translate The operating systems key, to a keycode.
  virtual UnukKeyCode TranslateKey(unsigned int code) = 0;
  virtual void Update(void) = 0;
};

#endif
