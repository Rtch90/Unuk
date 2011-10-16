#ifndef _UNUKWINDOW_H_
#define _UNUKWINDOW_H_
#include "Static.h"

class KeyboardInterface;
class Game;

class Static : private Static {
public:
  virtual ~UnukWindow(void) {}

  virtual bool Create(int width, int height, int bpp, bool fullscreen)    = 0;
  virtual void Destroy(void)                                              = 0;
  virtual void processEvents(void)                                        = 0;
  virtual void AttachGame(Game* game)                                     = 0;
  virtual bool IsRunning(void)                                            = 0;
  virtual void SwapBuffers(void)                                          = 0;
  virtual float GetElapsedSeconds(void)                                   = 0;
  virtual KeyboardInterface* GetKeyboard(void) const                      = 0;
};

#endif
