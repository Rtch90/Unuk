#include <ctime>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include "../Libs/wglext.h"
#include "Win32Window.h"
#include "../Unuk/Game.h"

typedef HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

Win32Window::Win32Window(HINSTANCE hInstance) {
  m_isRunning = false;
  m_game      = NULL;
  m_hinstance = hInstance;
  m_lastTime  = 0;
}

Win32Window::~Win32Window(void) {

}

bool Win32Window::Create(int width, int height, int bpp, bool fullscreen) {
  DWORD dwExStyle;
  DWORD dwStyle;
  
  m_isFullscreen = fullscreen;

  // Set up the window values.
  m_windowRect.left   = (long) 0;
  m_windowRect.right  = (long) width;
  m_windowRect.top    = (long) 0;
  m_windowRect.bottom = (long) height;

  // Set up the window class structure.
  m_windowClass.cbSize		= sizeof(WNDCLASSEX);
  m_windowClass.style		= CS_HREDRAW | CS_VREDRAW;
  m_windowClass.lpfnWndProc	= Win32Window::StaticWndProc; // Our static method is the event handler.
  m_windowClass.cbClsExtra	= 0;
  m_windowClass.cbWndExtra	= 0;
  m_windowClass.hInstance	= m_hinstance;
  m_windowClass.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
  m_windowClass.hCurser		= LoadCursor(NULL, IDC_ARROW);
  m_windowClass.hbrBackground	= NULL;
  m_windowClass.lpszMenuName	= NULL;
  m_windowClass.lpszClassName	= "Unuk";
  m_windowClass.hIconSm		= LoadIcon(NULL, IDI_WINLOGO);

  // Register the window class.
  if(!RegisterClassEx(&m_windowClass)) {
    return false;
  }

  // We need to change the display mode if we are running fullscreen.
  if(m_isFullsceen) {
    // This is the device mode.
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(smScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);

    // Set the screen width/height/bpp.
    dmScreenSettings.dmPelsWidth  = width;
    dmScreenSettings.dmPelsHeight = height;
    dmScreenSettings.dmBitsPerPel = bpp;
    dmScreenSettings.dwFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if(ChangeDisplaySettings(&dScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
      // Setting display mode failed, we will switch to windowed mode.
      MessageBox(NULL, "Display mode failed", NULL, MB_OK);
      m_isFullscreen = false;
    }
  }

  // Check to see if we are still in fullscreen mode.
  if(m_fullscreen) {
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle   = WS_POPUP;
    ShowCursor(false);
  } else {
    // fullscreen mode must have failed.
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle   = WS_OVERLAPPEDWINDOW
  }

  // Adjusted the window to the requested size.
  AdjustWindowRectEx(&m_windowRect, swStyle, false, dwExStyle);

  // Now the class is regestered we can finaly create the window.
  m_hWnd = CreateWindowEx(NULL, "Unuk", dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0,
			m_windowRect.right - m_windowRect.left, m_windowRect.bottom - m_windowRect.top,
			NULL, NULL, m_hinstance, this);

  // Let's make sure the window creation went as planned.
  if(!m_hWnd) return 0;

  m_hdc = GetDC(m_hWnd);

  // We know everything is ok, display and update the window now.
  ShowWindow(m_hWnd, SW_SHOW);
  UpdateWindow(m_hWnd);
 
  m_lastTime = GetTickCount() / 1000.0f;
  return true;
}

void Win32Window::Destroy(void) {
  // If we are in fullscreen we want to switch back to desktop, and show the mouse cursor.
  if(m_isFullscreen) {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(true);
  }
}

void Win32Window::AttachGame(Game* game) {
  m_game = game;
}

bool Win32Window::IsRunning(void) {
  return m_isRunning;
}

void Win32Window::ProccessEvents(void) {
  MSG msg;
  
  // While there are messages in the queue, store them in msg.
  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    // Process the messages one at a time.
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void Win32Window::SetupPixelFormat(void) {
  int pixelFormat;
  
  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),	// Size.
	1,				// Version.
	PFD_SUPPORT_OPENGL |		// OpenGL window.
	PFD_DRAW_TO_WINDOW |		// Render to window.
	PFD_DOUBLEBUFFER,		// Double buffer.
	PFD_TYPE_RGBA,			// Color type.
	32,				// Color Depth.
	0, 0, 0, 0, 0, 0,		// Color bits (ignored).
	0,				// No alpha buffer.
	0,				// Alpha bits (ignored).
	0,				// No accumulation buffer.
	0, 0, 0, 0,			// Accumulation bits (ignored).
	16,				// Depth buffer.
	0,				// No stencil buffer.
	0, 				// No auxiliary buffers.
	PFD_MAIN_PLANE,			// Main layer.
	0,				// Reserved.
	0, 0, 0,			// No layer, visible, damage masks.
  };

  pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
  SetPixelFormat(m_hdc, pixelFormat, &pfd);
}

LRESULT Win32Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch(uMsg) {
  // Create the window.
  case WM_CREATE:
    m_hdc = GetDC(hWnd);
    SetupPixelFormat();

    // Setup the OpenGL version. We want to use 3.0.
    int attribs[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 0,
      0
    };

    // Create a temporary context so we can get a pointer to the function.
    HGLRC tmpContext = wglCreateContext(m_hdc);
    // Make it the current.
    wglMakeCurrent(m_hdc, tmpContext);
    
    // Get the function pointer.
    wglCreateContextAttribsARB = (PFNWGLCCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");

    // If it is NULL, then GL 3.0 is not supported.
    if(!wglCreateContextAttribsARB) {
      Debug::logger->message("\nOpenGL 3.0 is not supported, falling back to GL 2.1");
      m_hglrc = tmpContext;
    } else {
      // Create an OpenGL 3.0 context using the new function.
      m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, attribs);
      // Delete then temp context.
      wglDeleteContext(tmpContext);
    }

    // Make the GL3 context current.
    wglMakeCurrent(m_hdc, m_hglrc);
    // Our window is now running.
    m_isRunning = true;
    break;
  case WM_DESTROY:
  case WM_CLOSE:
    wglMakeCurrent(m_hdc, NULL);
    wglDeleteContext(m_hglrc);
    m_isRunning = false;
    PostQuitMessage(0);
    return 0;
    break;
  case WM_SIZE:
    // Get the width and height.
    int height = HIWORD(lParam);
    int width  = LOWORD(lParam);
    getAttachedExample()->onResize(width, height);
    break;
  case WM_KEYDOWN:
    // If we detect the escape key, then please close the window.
    if(wParam == VK_ESCAPE) {
      DestroyWindow(m_hwnd);
    }
    break;
  default:
    break;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Win32Window::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  Win32Window* window = NULL;

  // If we see the create message.
  if(uMsg == WM_CREATE) {
    // Then get the pointer we stored during create.
    window = (Win32Window)(LPCREATESTRUCT)lParam)->lpCreateParams;
    // Associate the window pointer with the hWnd for the other events to access.
    SetWindowLongPtr(hWnd, GWL_USERDAA, (LONG_PTR)window);
  } else {
    // If this aint a creation event, then we should have stored a pointer to the window.
    window = (Win32Window)GetWindowLongPtr(hWnd, GWL_USERDATA);
    if(!window) {
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
  }
  // Call our window's member WndProc (allows us to access member variables).
  return window->WndProc(hWnd, uMsg, wParam, lParam)
}

float Win32Window::getElapsedSeconds() {
  float currentTime = float(GetTickCount()) / 1000.0f;
  float seconds	    = float(currentTime - m_lastTime);
  m_lastTime 	    = currentTime;
  return seconds;
}
