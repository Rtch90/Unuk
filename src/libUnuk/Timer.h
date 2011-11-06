#ifndef _TIMER_H_
#define _TIMER_H_
#include <SDL/SDL.h>
#include <string>
#include <sstream>
using namespace std;

class Timer {
public:
  Timer(void);
  ~Timer(void);

  void Pause(void);
  void Unpause(void);
  void Start(void);

  bool IsPaused(void) { return m_paused; }

  int GetTicks(void);

  string GetTicksStr(void);

private:
  bool m_paused;
  int  m_startTicks;
  int  m_pausedTicks;
};

#endif
