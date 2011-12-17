#ifndef _FPS_H_
#define _FPS_H_
#include "../Unuk/Globals.h"
#include "Timer.h"


class FPS {
public:
  FPS(void);
  ~FPS(void);

  void LimitFPS(void);

  void SetMaxFPS(int maxFPSArg);
  int GetMaxFPS(void)       { return _maxFPS; }

  int GetCurrentFPS(void)   { return _fps; }

private:
  int _fps;
  int _frame;
  int _maxFPS;

  Timer _frameTimer;
  Timer _fpsCalc;
};

#endif
