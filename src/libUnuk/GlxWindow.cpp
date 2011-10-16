#include <iostream>
#include <string>

#ifdef __unix__
#include <sys/time.h>
#endif

#include "../Unuk/Game.h"
#include "../Unuk/Player.h"
#include "GlxWindow.h"
#include "XKeyboardInterface.h"
#include "Debug.h"

using namespace std;

typedef GLXContext ( * PFNGLXCREATECONTEXTATTRIBSARBPROC) (Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);

unsigned int GetTickCount() {
  struct timeval t;
  gettimeofday(&t, NULL);

  unsigned long secs = t.tv_sec * 1000;
  secs += (t.tv_usec / 1000);
  return secs;
}

GlxWindow::GlxWindow(void) :
  m_game(NULL),
  m_isRunning(true),
  m_lastTime(0),
  m_display(NULL),
  m_XWindow(0),
  m_glContext(0),
  m_screenID(0),
  m_isFullscreen(false),
  m_width(0),
  m_height(0),
  m_bpp(0),
  m_GL3Supported(false),
  m_keyboard(NULL) {
    m_keyboard = new XKeyboardInterface();
  }

GlxWindow::~GlxWindow(void) {
  delete m_keyboard;
}

bool GlxWindow::Create(int width, int height, int bpp, bool fullscreen) {
  // Open up the default display.
  m_display = XOpenDisplay(0);
  if(m_display == NULL) {
    Debug::logger->message("\nCould not open the display.");
    return false;
  }

  // Get the ID of the default screen. 
  m_screenID = DefaultScreen(m_display);

  int n		= 0;
  int modeNum 	= 0;
  
  // Get the framebuffer config using the default attributes.
  GLXFBConfig framebufferConfig = (*glXChooseFBConfig(m_display, DefaultScreen(m_display), 0, &n));

  XF86VidModeModeInfo **modes;
  if(!XF86VidModeGetAllModeLines(m_display, m_screenID, &modeNum, &modes)) {
    Debug::logger->message("\nCould not query the video modes.");
    return false;
  }
  
  m_XF86DeskMode = *modes[0];
  
  int bestMode = - 1;
  for(int i = 0; i < modeNum; i++) {
    if((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height)) {
      bestMode = i;
    }
  }
  
  if(bestMode == -1) {
     Debug::logger->message("\nCould not find a suitable graphics mode.");
     return false;
  }

  int doubleBufferedAttribList[] = {
    GLX_RGBA, GLX_DOUBLEBUFFER,
    GLX_RED_SIZE,   4,
    GLX_GREEN_SIZE, 4,
    GLX_BLUE_SIZE,  4,
    GLX_DEPTH_SIZE, 16,
    None
  };

  XVisualInfo* vi = NULL;
  // Try to create a double buffered mode.
  vi = glXChooseVisual(m_display, m_screenID, doubleBufferedAttribList);
  
  if(vi == NULL) {
    Debug::logger->message("\nCould not create a double buffered window.");
    return false;
  }

  // Create a GL 2.1 context.
  GLXContext gl2Context = glXCreateContext(m_display, vi, 0, GL_TRUE);
  
  if(gl2Context == NULL) {
    Debug::logger->message("\nCould not create a GL 2.1 context, please check your graphics drivers.");
    return false;
  }

  // Get a pointer to the GL 3.0 context creation.
  PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribs = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((GLubyte*)"glXCreateContextAttribsARB");
  
  if(glXCreateContextAttribs == NULL) {
    Debug::logger->message("\nOpenGL 3.0 is not supported, falling back to 2.1.");
    m_glContext = gl2Context;
    m_GL3Supported = false;
  } else {
    // Create a GL 3.0 context.
    int attribs[] = {
      GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
      GLX_CONTEXT_MINOR_VERSION_ARB, 0,
      0
    };
    
    m_glContext = glXCreateContextAttribs(m_display, framebufferConfig, 0, true, &attribs[0]);
    // We can destroy the GL 2.0 context once the 3.0 one has been created.
    glXDestroyContext(m_display, gl2Context);
    m_GL3Supported = true;
  }

  Colormap cmap = XCreateColormap(m_display, RootWindow(m_display, vi->screen), vi->visual, AllocNone);
  m_XSetAttr.colormap = cmap;
  m_XSetAttr.border_pixel = 0;
  m_XSetAttr.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask |
			    StructureNotifyMask;
  
  m_XSetAttr.override_redirect = False;

  //unsigned long windowAttributes = CWBorderPixel | CWColormap | CWEventMask;

  if(fullscreen) {
    //windowAttributes = CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect;
    
    XF86VidModeSwitchToMode(m_display, m_screenID, modes[bestMode]);
    XF86VidModeSetViewPort(m_display, m_screenID, 0, 0);
    m_XSetAttr.override_redirect = true;
  }

  m_XWindow = XCreateWindow(m_display, RootWindow(m_display, vi->screen), 0, 0,
				width, height, 0, vi->depth, InputOutput, vi->visual,
				CWBorderPixel | CWColormap | CWEventMask, &m_XSetAttr);

  string title = "Unuk";

  if(fullscreen) {
    XWarpPointer(m_display, None, m_XWindow, 0, 0, 0, 0, 0, 0);
    XMapRaised(m_display, m_XWindow);
    XGrabKeyboard(m_display, m_XWindow, true, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(m_display, m_XWindow, true, ButtonPressMask, GrabModeAsync,
    GrabModeAsync, m_XWindow, None, CurrentTime);

    m_isFullscreen = true;
  } else {
    Atom wmDelete = XInternAtom(m_display, "WM_DELETE_WINDOW", true);
    XSetWMProtocols(m_display, m_XWindow, &wmDelete, 1);
    XSetStandardProperties(m_display, m_XWindow, title.c_str(), None, 16, NULL, 0, NULL);
    XMapRaised(m_display, m_XWindow);
  }

  XFree(modes);

  // Let's make the new context current.
  glXMakeCurrent(m_display, m_XWindow, m_glContext);

  int posx = 0;
  int posy = 0;
  Window winDummy;
  unsigned int borderDummy;

  m_width  = (unsigned) width;
  m_height = (unsigned) height;
  m_bpp	   = (unsigned) bpp;

  XGetGeometry(m_display, m_XWindow, &winDummy,
                 &posx, &posy, &m_width, &m_height,
                 &borderDummy, &m_bpp);

  // Initialize the time.
  m_lastTime = GetTickCount();
  return true;
}

void GlxWindow::Destroy() {
  if(m_glContext) {
    glXMakeCurrent(m_display, None, NULL);
    glXDestroyContext(m_display, m_glContext);
    m_glContext = NULL;
  }

  if(m_isFullscreen) {
    XF86VidModeSwitchToMode(m_display, m_screenID, &m_XF86DeskMode);
    XF86VidModeSetViewPort(m_display, m_screenID, 0, 0);
  }
  
  XCloseDisplay(m_display);
}

void GlxWindow::ProcessEvents(void) {
  GetKeyboard()->Update();

  XEvent event;
  while(XPending(m_display) > 0) {
    XNextEvent(m_display, &event);
    switch(event.type) {
    case Expose:
      if(event.xexpose.count != 0) break;
      break;
    case ConfigureNotify: {
        int width  = event.xconfigure.width;
        int height = event.xconfigure.height;
        GetAttachedGame()->OnResize(width, height);
      }    
      break;
    case KeyPress: {
        if(XLookupKeysym(&event.xkey, 0) == XK_Escape) {
          m_isRunning = false;
        }
        // Register the key press with the keyboard interface.
        m_keyboard->HandleKeyDown(m_keyboard->TranslateKey(XLookupKeysym(&event.xkey,0)));

        // -- Big Hack! I will process all events from here.
        if(m_keyboard->IsKeyHeldDown(U_w)) { m_player->SetVelocity(1,1); }
      }
      break;
    case KeyRelease: {
        UnukKeyCode code = m_keyboard->TranslateKey(XLookupKeysym(&event.xkey,0));
        m_keyboard->HandleKeyUp(code);
      }
      break;
    case ClientMessage:
      if(string(XGetAtomName(m_display, event.xclient.message_type)) == string("WM_PROTOCOLS")) {
        m_isRunning = false;
      }
      break;
    default:
      break;
    }
  }
}

float GlxWindow::GetElapsedSeconds(void) {
  unsigned int currentTime = GetTickCount();
  unsigned int diff	   = currentTime - m_lastTime;
  m_lastTime = currentTime;
  return float(diff) / 1000.0f;
}
