#pragma once
#include <string>
#include <list>

#include "Text.h"
#include "../System/Rect.h"
#include "../System/Timer.h"

class EventHistory {
public:
  EventHistory(void);
  ~EventHistory(void);

  void LogEvent(const std::string& evtText);

  void Render(void);

private:
  std::list<std::string> _events;
  Text _text;
  Rect _background;

  Timer _timeToVanish;
  bool _visible;

  int _bgx;
  int _bgy;

  static const int BOX_WIDTH;
  static const int BOX_HEIGHT;
};