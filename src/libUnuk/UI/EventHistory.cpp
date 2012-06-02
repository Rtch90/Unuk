#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "EventHistory.h"
#include "../../Unuk/Constants.h"
#include "../../Unuk/Globals.h"

const int EventHistory::BOX_WIDTH   = 350;
const int EventHistory::BOX_HEIGHT  = 140;

EventHistory::EventHistory(void) {
  _bgx = SCREEN_WIDTH / 2 - BOX_WIDTH / 2;
  _bgy = 10;

  _titleText.SetXY(_bgx + BOX_WIDTH/2, _bgy + 5);
  _titleText.SetTextBlended("Unuk Log", small, 0, 255, 255);
  _titleText.SetXY(_titleText.GetX() - _titleText.GetWidth()/2, _titleText.GetY());

  _text.SetXY(_bgx + 5, _bgy + 30);

  _visible = false;
}

EventHistory::~EventHistory(void) {
}

void EventHistory::LogEvent(const std::string& evtText) {
  _events.push_back(evtText);

  if(_events.size() > 4) {
    _events.erase(_events.begin());
  }

  BakeText();

  if(!_visible) {
    _timeToVanish.Start();
    _visible = true;
  }
}

void EventHistory::Render(void) {
  if(_visible && (_timeToVanish.GetTicks() >= 5000)) {
    _timeToVanish.Stop();

    _events.erase(_events.begin());

    if(_events.empty()) {
      _visible = false;
    } else {
      BakeText();
      _timeToVanish.Start();
    }
  }

  if(!_visible) {
    return;
  }

  roundedBoxRGBA(screen,
                 _bgx, _bgy,
                 _bgx + BOX_WIDTH, _bgy + BOX_HEIGHT,
                 8,
                 0, 0, 0, 128);

  roundedRectangleRGBA(screen,
                       _bgx, _bgy,
                       _bgx + BOX_WIDTH, _bgy + BOX_HEIGHT,
                       8,
                       0, 255, 255, 255);

  _titleText.RenderLiteral();
  _text.RenderLiteral();
}

void EventHistory::BakeText(void) {
  std::string textStr;
  for(std::list<std::string>::iterator evIt = _events.begin(); evIt != _events.end(); ++evIt) {
    textStr.append(*evIt);
    textStr.append("\n");
  }

  _text.SetTextBlended(textStr, small, 255, 255, 255);
}

