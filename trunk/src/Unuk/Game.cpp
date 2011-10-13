#ifdef WIN32
#include <windows.h>
#endif

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>

#include "SDL/SDL.h"
#include "Game.h"
#include "Player.h"
#include "../libUnuk/Sprite.h"
#include "../libUnuk/Debug.h"

Game::Game(void) {
  m_rotationAngle = 0.0f;
}

Game::~Game(void) {

}

bool Game::Init(void) {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  return true;
}

void Game::Prepare(float dt) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  Sprite::Enable2D();

  m_player->Prepare();

  const float SPEED = 15.0f;
  m_rotationAngle += SPEED * dt;
  if(m_rotationAngle > 360.0f) {
    m_rotationAngle -= 360.0f;
  }

}

void Game::Render(void) {
  static GLint T0	= 0;
  static GLint frames	= 0;

  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0, 0);

  // Draw the test image.
  m_player->Render();

  glFlush();
  //glutSwapBuffers();
  glDisable(GL_TEXTURE_2D);
 
  // Get frames per second.
  frames++;
  {
    GLint t = SDL_GetTicks();
    if (t - T0 >= 5000) {
      GLfloat seconds = (t - T0) / 1000.0f;
      GLfloat fps = frames / seconds;
      Debug::logger->message("\n%d frames in %g seconds = %g FPS", frames, seconds, fps);
      T0 = t;
      frames = 0;
    }
  }
}

void Game::Shutdown(void) {
  Debug::logger->message("\n\n-----Cleaning Up-----");
  m_player->CleanUp();
  Debug::logger->message("\nPlayer Deleted.");
  Debug::closeLog();
}

void Game::UpdateProjection(void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set up the orthographic projection.
  glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Game::OnResize(int width, int height) {
  // Let's see you divide by zero now!
  if(height == 0) { height = 1; }

  // Set the viewport to the window size.
  glViewport(0, 0, width, height);

  // Set the projection.
  UpdateProjection();
}
