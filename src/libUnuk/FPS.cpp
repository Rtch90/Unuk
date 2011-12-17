#include "FPS.h"

FPS::FPS(int maxFPSArg) {
  _maxFPS = maxFPSArg;

  _fps = 0;
  _frame = 0;

  _frameTimer.Start();
  _fpsCalc.Start();
}

FPS::~FPS(void) {

}

void FPS::LimitFPS(void) {
  // Calculate the FPS.
  if(_fpsCalc.GetTicks() > 1000) {

    _fps = _frame / (_fpsCalc.GetTicks() / 1000);

    _fpsCalc.Start();
    _frame = 0;
  }

  // Put a limitation on the FPS.
  if(1000 / _maxFPS  > _frameTimer.GetTicks()) {
    // SDL_Delay does not accept a float so for higher framerate
    // limits there's an innacuracy. This is as much as 3fps
    // at a limit of 60fps.
    SDL_Delay((1000 / _maxFPS) - _frameTimer.GetTicks());
  }

  _frameTimer.Start();
  _frame++;
}

void FPS::SetMaxFPS(int maxFPSArg) {
  _maxFPS = maxFPSArg;
}
