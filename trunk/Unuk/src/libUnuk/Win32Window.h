#ifndef _WIN32WINDOW_H_
#define _WIN32WINDOW_H_
#include <windows.h>
#include <ctime>

class Game; // Declaration of our Game class.

class Win32Window {
public:
  // Default constructor/deconstructor.
  Win32Window(HINSTANCE hInstance);
  ~Win32Window(void);

  bool Create(int width, int height, int bpp, bool fullscreen);
  void Destroy();
  void ProcessEvents();
  void AttachGame(Game* game);

  // Is the window running?
  bool IsRunning();
  
  void SwapBuffers() { SwapBuffers(m_hdc); }

  static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

  float GetElapsedSeconds();

private:       
  // Pointer to the game class.
  Game* m_game;
  // Is the window still running?
  bool m_isRunning;
  bool m_fullscreen;

  // Window handle.
  HWND m_hWnd;
  // This is our rendering context.
  HGLRC m_hglrc;
  // The device context.
  HDC m_hdc;
  // Window bounds.
  RECT m_windowRect;
  // Application instance.
  HINSTANCE m_hinstance;
  WNDCLASSEX m_windowClass;

  void SetupPixelFormat(void);
  Game* GetAttachedGame() { return m_game; }

  float m_lastTime;
};

#endif // _WIN32WINDOW_H_
