#ifdef __unix__
#include <sys/time.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"
#include "Game.h"
#include "../libUnuk/Input.h"
#include "../libUnuk/Debug.h"

// Screen width, height, and bit depth.
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 16;

// Define our SDL surface.
SDL_Surface *surface;

void Quit(int returnCode) {
  Debug::logger->message("-----Cleaning Up------");
  // Clean up the window.
  SDL_Quit();
  Debug::logger->message("Window destroyed!");
  Debug::closeLog();
  // And exit appropriately.
  exit(returnCode);
}

// Reset our viewport after a window resize.
int ResizeWindow(int width, int height) {
  // Height and width ration.
  GLfloat ratio;

  // Prevent devide by zero.
  if(height == 0)
    height = 1;

  ratio = (GLfloat )width / (GLfloat)height;

  // Setup our viewport.
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);

  // Change to the projection matrix and set our viewing volume.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set our perspective.
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  // Change to the MODELVIEW.
  glMatrixMode(GL_MODELVIEW);

  // Reset The View.
  glLoadIdentity();

  return 1;
}

void ProcessEvents(SDL_keysym *keysym) {
  switch(keysym->sym) {
  case SDLK_ESCAPE:
    // Quit if we detect 'esc' key.
    Quit(0);
    break;
  case SDLK_F1:
    // Fullscreen.
    SDL_WM_ToggleFullScreen(surface);
    break;
  default:
    break;
  }
  return;
}

int InitGL(void) {

  // Enable smooth shading.
  glShadeModel(GL_SMOOTH);

  // Set the background black.
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Depth buffer setup.
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // Nice Perspective Calculations.
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  return 1;
}

unsigned int GetTickCount() {
  struct timeval t;
  gettimeofday(&t, NULL);

  unsigned long secs = t.tv_sec * 1000;
  secs += (t.tv_usec / 1000);
  return secs;
}

float GetElapsedSeconds(void) {
  unsigned int lastTime = 0;
  unsigned int currentTime = GetTickCount();
  unsigned int diff = currentTime - lastTime;
  lastTime = currentTime;
  return float(diff) / 1000.0f;
}

int main() {
  // Initialize our Debug log.
  Debug::openLog(true);
  Debug::logger->message("-----Debug Initialized-----");

  int videoFlags;
  bool done = false;
  SDL_Event event;
  const SDL_VideoInfo *videoInfo;
  Game game;

  // Initialize SDL.
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError());
    Quit(1);
  }

  // Fetch the video info.
  videoInfo = SDL_GetVideoInfo();

  // Set the window caption.
  SDL_WM_SetCaption("Unuk", NULL);

  if(!videoInfo) {
    fprintf( stderr, "Video query failed: %s\n", SDL_GetError());
    Quit(1);
  }

  // Pass some flags to SDL_SetVideoMode.
  videoFlags  = SDL_OPENGL;
  videoFlags |= SDL_GL_DOUBLEBUFFER;
  videoFlags |= SDL_HWPALETTE;
  videoFlags |= SDL_RESIZABLE;

  // Can the surface be stored in memory?
  if(videoInfo->hw_available)
    videoFlags |= SDL_HWSURFACE;
  else
    videoFlags |= SDL_SWSURFACE;

  // Can we perform blitting on the GPU?
  if(videoInfo->blit_hw)
    videoFlags |= SDL_HWACCEL;

  // Set up the OpenGL double buffer.
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Get an SDL surface.
  surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, videoFlags);

  // Is there an SDL surface?
  if(!surface) {
    fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
    Quit(1);
  }

  // Initialize OpenGL.
  InitGL();

  // Resize the initial window.
  ResizeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
  Debug::logger->message("\n\n-----Engine Initialization Complete-----");
  Debug::logger->message("\n\n-----Logic-----");

  while(!done) {
    CreateInput();
    // Time to poll events.
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_VIDEORESIZE:
        // Handle resize events.
        surface = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, videoFlags);
        if(!surface) {
          fprintf(stderr, "Could not get a surface after resize: %s\n", SDL_GetError());
          Quit(1);
        }
        ResizeWindow(event.resize.w, event.resize.h);
        break;
      case SDL_KEYDOWN:
        // handle keydown events.
        ProcessEvents(&event.key.keysym);
        break;
      case SDL_QUIT:
        // Handle quit events.
        done = true;
        break;
      default:
        break;
      }
      UpdateInput();
    }
    // Render the scene.
    float elapsedTime = GetElapsedSeconds();
    //game.ProcessEvents();
    game.Prepare(elapsedTime);
    game.Render();
    SDL_GL_SwapBuffers();
  }
  game.Shutdown();
  // Clean ourselves up and exit.
  Quit(0);

  // We should never get here.
  return(0);
}

