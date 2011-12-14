#ifndef _TIMER_H_
#define _TIMER_H_
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

  bool IsPaused(void)  { return m_paused; }
  bool IsStarted(void) { return m_started; }

  int GetTicks(void);

  string GetTicksStr(void);

private:
  bool m_paused;
  bool m_started;

  int  m_startTicks;
  int  m_pausedTicks;
};

#endif
