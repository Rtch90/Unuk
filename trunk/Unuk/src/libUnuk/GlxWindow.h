#ifndef _GLXWINDOW_H_
#define _GLXWINDOW_H_
#define GLX_GLXEXT_LEGACY // This must be declared so the local glxext.h is used instead of the system one.
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include <ctime>
#include "../Libs/glxext.h"

// Declare some classes.
class Game;
class Player;
class KeyboardInterface;

class GlxWindow {
public:
  GlxWindow(void);
  virtual ~GlxWindow(void);

  bool Create(int width, int height, int bpp, bool fullscreen);
  void Destroy(void);
  void ProcessEvents(void);
  void AttachGame(Game* game) { m_game = game; }

  bool IsRunning(void) { return m_isRunning; }

  void SwapBuffers(void) { glXSwapBuffers(m_display, m_XWindow); }
  
  float GetElapsedSeconds(void);

  KeyboardInterface* GetKeyboard(void) const { return m_keyboard; }

private:
  Game* m_game;
  Player* m_player;
  bool m_isRunning;
 
  Game* GetAttachedGame(void) { return m_game; }

  unsigned int m_lastTime;

  Display*              m_display;
  Window                m_XWindow;
  GLXContext            m_glContext;
  XF86VidModeModeInfo   m_XF86DeskMode;
  XSetWindowAttributes  m_XSetAttr;
  int                   m_screenID;

  bool            m_isFullscreen;
  unsigned int 		m_width;
  unsigned int 		m_height;
  unsigned int 		m_bpp;

  bool            m_GL3Supported;
  KeyboardInterface* m_keyboard;
};

#endif // _GLXWINDOW_H_
