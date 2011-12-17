#include "Timer.h"

Timer::Timer(void) {
  _startTicks  = 0;
  _pausedTicks = 0;
  _paused  = false;
  _started = false;
}

Timer::~Timer(void) {
}

void Timer::Start(void) {
  _paused  = false;
  _started = true;
  _startTicks = SDL_GetTicks();
}

void Timer::Stop(void) {
  _paused  = false;
  _started = true;
}

void Timer::Pause(void) {
  assert(_paused == false);
  _paused = true;

  _pausedTicks = SDL_GetTicks() - _startTicks;
}

void Timer::Unpause(void) {
  assert(_paused == true);
  _paused = false;

  _startTicks = SDL_GetTicks() - _pausedTicks;

  _pausedTicks = 0;
}

int Timer::GetTicks(void) {
  if(_paused == true)
    return _pausedTicks;
  else if(_started == true)
    return SDL_GetTicks() - _startTicks;
  else
    return 0;
}

string Timer::GetTicksStr(void) {
  stringstream str;
  str << GetTicks() << "ms";

  return str.str();
}
