#include "EventHistory.h"
#include "../../Unuk/Constants.h"

const int EventHistory::BOX_WIDTH   = 350;
const int EventHistory::BOX_HEIGHT  = 130;

EventHistory::EventHistory(void) {
  _background.SetXY(SCREEN_WIDTH/2 - BOX_WIDTH/2, 10);
  _background.SetWidthHeight(BOX_WIDTH, BOX_HEIGHT);
  _background.SetRGB(0, 0, 0);

  _text.SetXY(_background.GetX() + 5, _background.GetY() + 5);
  
  _visible = false;
}

EventHistory::~EventHistory(void) {
}

void EventHistory::LogEvent(const std::string& evtText) {
  _events.push_back(evtText);

  if(_events.size() > 5) {
    _events.erase(_events.begin());
  }

  std::string textStr;
  for(std::list<std::string>::iterator evIt = _events.begin(); evIt != _events.end(); ++evIt) {
    textStr.append(*evIt);
    textStr.append("\n");
  }

  _text.SetTextBlended(textStr, small, 255, 255, 255);

  _timeToVanish.Start();
  _visible = true;
}

void EventHistory::Render(void) {
  if(_visible && (_timeToVanish.GetTicks() >= 2500)) {
    _timeToVanish.Stop();
    _visible = false;
  }

  if(!_visible) {
    return;
  }

  _background.DrawLiteral();
  _text.RenderLiteral();
}