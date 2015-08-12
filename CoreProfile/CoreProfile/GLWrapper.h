#ifndef GL_ENGINE_H
#define GL_ENGINE_H

#pragma comment (lib, "opengl32.lib")

#include <iostream>
#include <Windows.h>
#include "gl/gl3w.h"
#include "resource.h"

#include "KeyBinder.h"

class GLWrapper
{
  const char* className = "GLFramework";
  const int numBits = 32;

  HDC       hDC;                  // global device context
  HGLRC     hRC;                  // global rendering context
  HWND      hWnd;                 // handle of our window
  HINSTANCE hInstance;            // application instance

  HMENU     hMenu;

  bool isInitialized;
  bool isFullscreen;
  bool isDone;

  int width, height;

  bool InitializeGL();

public:
  GLWrapper();
  ~GLWrapper();

  bool CreateGLWindow(const char *title, LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM));

  HDC& GetDeviceContext(){ return hDC; }
  HGLRC& GetRenderingContext(){ return hRC; }
  HWND& GetHWND(){ return hWnd; }
};

#endif