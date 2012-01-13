#pragma once
#include <SDL/SDL.h>
#include <string>
#include <assert.h>
#include <sstream>
using namespace std;

class Timer {
public:
  Timer(void);
  ~Timer(void);

  void Pause(void);
  void Unpause(void);
  void Start(void);
  void Stop(void);

  bool IsPaused(void)  { return _paused; }
  bool IsStarted(void) { return _started; }

  int GetTicks(void);

  string GetTicksStr(void);

private:
  bool _paused;
  bool _started;

  int  _startTicks;
  int  _pausedTicks;
};
