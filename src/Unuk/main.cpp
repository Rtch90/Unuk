#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define GLX_GLXEXT_LEGACY // Defined so we use our own glxext.h, rather than the system one.

#ifdef WIN32
#include <windows.h>
#include "../libUnuk/Win32Window.h"
#else
#include "../libUnuk/GlxWindow.h"
#endif

#include <SDL/SDL.h>
#include "Game.h"
#include "../libUnuk/Debug.h"

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
#else
int main(/*int argc, char** argv*/) {
#endif
  // Initialize our Debug log.
  Debug::openLog(true);
  Debug::logger->message("-----Debug Initialized-----");
  // Set our window settings.
  const int windowWidth 	= 800;
  const int windowHeight	= 600;
  const int windowBPP		= 16;
  const int windowFullscreen	= false;

#ifdef WIN32
  // This is our window.
  Win32Window programWindow(hInstance);
#else
  GlxWindow programWindow;
#endif

  // Set SDL up so we can use it for input and crap.
  SDL_Init(SDL_INIT_EVERYTHING);

  // The Game code.
  Game game;

  // Attach the game to our window.
  programWindow.AttachGame(&game);

  // Attempt to create the window.
  if(!programWindow.Create(windowWidth, windowHeight, windowBPP, windowFullscreen)) {
    // If it fails to be created...
#ifdef WIN32
    MessageBox(NULL, "Unable to create the OpenGL window.", "Error", MB_ICONERROR | MB_OK);
#endif
    // Reset the display and exit.
    programWindow.Destroy();
    return 1;
  }

  // Make sure our game is initialized.
  if(!game.Init()) {
#ifdef WIN32
    MessageBox(Null, "Could not initialize the application", "Error", MB_ICONERROR | MB_OK);
#endif
    // Reset the display and exit.
    programWindow.Destroy();
    return 1;
  }

  Debug::logger->message("\n\n-----Engine Initialization Complete-----");
  Debug::logger->message("\n\n-----Logic-----");
  // Main loop: We render frames untill IsRunning returns false.
  while(programWindow.IsRunning()) {
    // Process the window events.
    programWindow.ProcessEvents();
    
    // Get the time that passed since the last frame.
    float elapsedTime = programWindow.GetElapsedSeconds();

    //Perform any logic before rendering.
    game.Prepare(elapsedTime);
    // Let us now render the scene.
    game.Render();

    programWindow.SwapBuffers();
  }
                  
  // Free any recources used.
  game.Shutdown();
  // Destroy the window.
  programWindow.Destroy();

  // Sucess!!!11one!one1!
  return 0;
}
