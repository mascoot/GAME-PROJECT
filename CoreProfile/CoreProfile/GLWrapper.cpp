#include "GLWrapper.h"
#include "gl/gl3w.c"

GLWrapper::GLWrapper() : isInitialized(false)
{
  width = 1280;
  height = 720;
  isFullscreen = false;
  hWnd = nullptr;
}

/******************************************************************************/
/*!
\brief
Deletes the DC, RC, and Window, and restores the original display.
*/
/******************************************************************************/
GLWrapper::~GLWrapper()
{
  DestroyMenu(hMenu);

  // restore the original display if we're in fullscreen mode
  if (isFullscreen)
  {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(true);
  }

  // if we have an RC, release it
  if (hRC)
  {
    // release the RC
    if (!wglMakeCurrent(NULL, NULL))
      MessageBox(NULL, "Unable to release rendering context", "Error", MB_OK | MB_ICONINFORMATION);

    // delete the RC
    if (!wglDeleteContext(hRC))
      MessageBox(NULL, "Unable to delete rendering context", "Error", MB_OK | MB_ICONINFORMATION);

    hRC = NULL;
  }

  // release the DC if we have one
  if (hDC && !ReleaseDC(hWnd, hDC))
  {
    MessageBox(NULL, "Unable to release device context", "Error", MB_OK | MB_ICONINFORMATION);
    hDC = NULL;
  }

  // destroy the window if we have a valid handle
  if (hWnd && !DestroyWindow(hWnd))
  {
    MessageBox(NULL, "Unable to destroy window", "Error", MB_OK | MB_ICONINFORMATION);
    hWnd = NULL;
  }

  // unregister our class so we can create a new one if we need to
  if (!UnregisterClass(className, hInstance))
  {
    MessageBox(NULL, "Unable to unregister window class", "Error", MB_OK | MB_ICONINFORMATION);
    hInstance = NULL;
  }
}

/******************************************************************************/
/*!
\fn     bool CreateWindowContext(   const char *title, int width, int height,
int numBits, bool fullscreen)
\brief
Create the window and everything else we need, including the device and
rendering context. If a fullscreen window has been requested but can't be
created, the user will be prompted to attempt windowed mode.

Returns true if everything goes well, or false if an unrecoverable error
occurs. Note that if this is called twice within a program, KillWindow needs
to be called before subsequent calls to CreateWindowContext.
\param  title
Title of the window.
\param  width
Width of the window area, excluding menu, border, ...
\param  height
Height of the window area, excluding menu, border, ...
\param  numBits
Number of bits that we want to use.
\param  fullscreen
Whether the window should be full-screen.
*/
/******************************************************************************/
bool GLWrapper::CreateGLWindow(const char *title, LRESULT(CALLBACK* proc)(HWND, UINT, WPARAM, LPARAM))
{
  // get our instance handle
  hInstance = GetModuleHandle(NULL);

  WNDCLASSEX  wc;    // window class

  // fill out the window class structure
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = proc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));  // default icon
  wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));      // windows logo small icon
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);      // default arrow
  wc.hbrBackground = NULL;     // no background needed
  wc.lpszMenuName = NULL;     // no menu
  wc.lpszClassName = className;

  // register the windows class
  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL, "Unable to register the window class", "Error", MB_OK | MB_ICONEXCLAMATION);
    // exit and return false
    return false;
  }

  // if we're in fullscreen mode, set the display up for it
  if (isFullscreen)
  {
    //Get primary monitor screen resolution
    //width = GetSystemMetrics(SM_CXSCREEN);
    //height = GetSystemMetrics(SM_CYSCREEN);

    // set up the device mode structure
    DEVMODE screenSettings;
    memset(&screenSettings, 0, sizeof(screenSettings));

    screenSettings.dmSize = sizeof(screenSettings);
    screenSettings.dmPelsWidth = width;    // screen width
    screenSettings.dmPelsHeight = height;   // screen height
    screenSettings.dmBitsPerPel = numBits;     // bits per pixel
    screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // attempt to switch to the resolution and bit depth we've selected
    if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      // if we can't get fullscreen, let them choose to quit or try windowed mode
      if (MessageBox(NULL, "Cannot run in the fullscreen mode at the selected resolution\n"
        "on your video card. Try windowed mode instead?",
        "Warning",
        MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
        isFullscreen = false;
      else
        return false;
    }
  }

  DWORD dwExStyle;
  DWORD dwStyle;

  // set the window style appropriately, depending on whether we're in fullscreen mode
  if (isFullscreen)
  {
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle = WS_POPUP;           // simple window with no borders or title bar
    ShowCursor(true);            // hide the cursor for now
  }
  else
  {
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }

  // set up the window we're rendering to so that the top left corner is at (0,0)
  // and the bottom right corner is (height,width)
  RECT  windowRect;
  windowRect.left = 0;
  windowRect.right = (LONG)width;
  windowRect.top = 0;
  windowRect.bottom = (LONG)height;

  // change the size of the rect to account for borders, etc. set by the style
  AdjustWindowRectEx(&windowRect, dwStyle, true, dwExStyle);

  hMenu = ::LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

  // class registered, so now create our window
  hWnd = CreateWindowEx(dwExStyle,          // extended style
    className,          // class name
    title,              // app name
    dwStyle |           // window style
    WS_CLIPCHILDREN |   // required for
    WS_CLIPSIBLINGS,    // using OpenGL
    0, 0,               // x,y coordinate
    windowRect.right - windowRect.left, // width
    windowRect.bottom - windowRect.top, // height
    NULL,               // handle to parent
    //hMenu,              // handle to menu, use NULL if not needed
    NULL,
    hInstance,          // application instance
    NULL);              // no extra params

  // see if our window handle is valid
  if (!hWnd)
  {
    MessageBox(NULL, "Unable to create window", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // get a device context
  if (!(hDC = GetDC(hWnd)))
  {
    MessageBox(NULL, "Unable to create device context", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // set the pixel format we want
  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),  // size of structure
    1,                              // default version
    PFD_DRAW_TO_WINDOW |            // window drawing support
    PFD_SUPPORT_OPENGL |            // OpenGL support
    PFD_DOUBLEBUFFER,               // double buffering support
    PFD_TYPE_RGBA,                  // RGBA color mode
    numBits,                        // 32 bit color mode
    0, 0, 0, 0, 0, 0,               // ignore color bits, non-palettized mode
    0,                              // no alpha buffer
    0,                              // ignore shift bit
    0,                              // no accumulation buffer
    0, 0, 0, 0,                     // ignore accumulation bits
    16,                             // 16 bit z-buffer size
    8,                              // no stencil buffer
    0,                              // no auxiliary buffer
    PFD_MAIN_PLANE,                 // main drawing plane
    0,                              // reserved
    0, 0, 0 };                      // layer masks ignored

  unsigned int  pixelFormat;

  // choose best matching pixel format
  if (!(pixelFormat = ChoosePixelFormat(hDC, &pfd)))
  {
    MessageBox(NULL, "Can't find an appropriate pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // set pixel format to device context
  if (!SetPixelFormat(hDC, pixelFormat, &pfd))
  {
    MessageBox(NULL, "Unable to set pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // show the window in the forground, and set the keyboard focus to it
  ShowWindow(hWnd, SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);

  return InitializeGL();
}

bool GLWrapper::InitializeGL()
{
    // create the OpenGL rendering context
    if (!(hRC = wglCreateContext(hDC)))
    {
        MessageBox(NULL, "Unable to create OpenGL rendering context", "Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    // now make the rendering context the active one
    if (!wglMakeCurrent(hDC, hRC))
    {
        MessageBox(NULL, "Unable to activate OpenGL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    /* GL3W Initialization */
    if (gl3wInit())
    {
        MessageBox(NULL, "Failed to initialize OpenGL", "Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    if (!gl3wIsSupported(3, 3))
    {
        MessageBox(NULL, "OpenGL 3.3 not supported", "Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL version  : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

    return isInitialized = true;
}