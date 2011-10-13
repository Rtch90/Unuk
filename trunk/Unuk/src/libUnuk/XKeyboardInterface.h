#ifndef XKEYBOARDINTERFACE_H
#define XKEYBOARDINTERFACE_H
#ifdef __unix__
#include <cstring>
#include "KeyboardInterface.h"
#include "Debug.h"

class XKeyboardInterface : public KeyboardInterface {
public:
  XKeyboardInterface(void) {
    for(int i = 0; i < U_MAX_KEYS; ++i) {
      m_keyState[i]      = 0;
      m_lastKeyState[i]  = 0;
    }
  }

  virtual bool IsKeyPressed(UnukKeyCode code) {
    return(m_lastKeyState[code] && m_keyState[code] == 1);
  }

  virtual bool IsKeyHeldDown(UnukKeyCode code) {
    return(m_lastKeyState[code] && m_keyState[code]);
  }

  virtual void HandleKeyDown(UnukKeyCode code) {
    m_keyState[code] = 1;
  }

  virtual void HandleKeyUp(UnukKeyCode code) {
    m_keyState[code] =0;
  }

  UnukKeyCode TranslateKey(unsigned int code) {
    switch(code) {
    case XK_Up:
      return U_UP;
      break;
    case XK_Down:
      return U_DOWN;
      break;
    case XK_Left:
      return U_LEFT;
      break;
    case XK_Right:
      return U_RIGHT;
      break;
    case XK_space:
      return U_SPACE;
      break;
    case XK_w:
      return U_w;
      break;
    case XK_a:
      return U_a;
      break;
    case XK_s:
      return U_s;
      break;
    case XK_d:
      return U_d;
      break;
    default:
      Debug::logger->message("Warning: Can not translate this key");
      return U_INVALID;
    }
  }

  void Update(void) {
    // Copy the current key to the last key state.
    memcpy(m_lastKeyState, m_keyState, sizeof(short) * U_MAX_KEYS);
  }

private:
  short m_keyState[U_MAX_KEYS];
  short m_lastKeyState[U_MAX_KEYS];
};

// __unix__
#endif
// XKEYBOARDINTERFACE_H
#endif
