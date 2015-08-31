#include "resource.h"
#include "Engine.h"

/********************************* Globals **********************************/
bool      isDone = false;
bool      minimized = false;     // true if window is minimized


/******************************** Prototypes ********************************/

#define APP_TITLE       "Core Framework!"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/******************************************************************************/
/*!
\fn     int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
LPSTR lpCmdLine, int nShowCmd)
\brief
Main function of the program. It:
- Allocates a console for debugging purpose.
- Creates the window and device context/rendering context.
- Intializes OpenGL function pointers.
- Set up all graphics-related stuffs.
- Handles interactions with the user (mouse, menu bar, ...).
- Renders the scene.
- Cleans up graphics-related stuffs and kill the device context/
rendering context/window upon program termination.

\param  hInstance
Handler for the current instance of the program.
\param  hPrevInstance
Handler for the previous instance of the program.
\param  lpCmdLine
Program command line.
\param  nShowCmd
Control how the window is to be shown (HIDDEN/MINIMIZED/MAXIMIZED/...)
*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  GLWrapper glWrap;
  // By default WinAPI program turns off the console. But we turn it on again for debugging purpose.
  AllocConsole();
  freopen("CONOUT$", "w", stdout);

  // if the window is set up correctly, we can proceed with the message loop
  if (glWrap.CreateGLWindow("GLFramework!", WndProc))
    isDone = false;
  else
    isDone = true;

  MSG   msg;       // message
  InputManager inputman;
  GameEngine engine;

  // main message loop
  while (!isDone)
  {
    if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)   // do we receive a WM_QUIT message?
        isDone = true;              // if so, time to quit the application
      else
      {
        TranslateMessage(&msg);     // translate and dispatch to event queue
        DispatchMessage(&msg);
      }
    }
    // don't update the scene if the app is minimized
    if (!minimized)
    {
      engine.Update();
      //Check for keyboard input
      if (inputman.KeyPressed(VK_ESCAPE)) isDone = true;

      glClearColor(0, 0, 0, 1); // black
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      engine.Render();

      // switch the front and back buffers to display the updated scene faster
      SwapBuffers(glWrap.GetDeviceContext());
    }
  }
  return msg.wParam;
}

/******************************************************************************/
/*!
\fn     LRESULT CALLBACK WndProc(   HWND hwnd, UINT message,
WPARAM wParam, LPARAM lParam)
\brief
Windows message handler.
\param  hwnd
Handler to the window.
\param  message
The message based on user input (mouse/keyboard/menu...)
\param  wParam
Additional message parameters. See examples below.
\param  lParam
Additional message parameters. See examples below.
*/
/******************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_ACTIVATE:  // watch for the window being minimized and restored
		{
			if (!HIWORD(wParam))
				// program was restored or maximized
				minimized = false;
			else
				// program was minimized
				minimized = true;

			return 0;
		}

		case WM_SYSCOMMAND:  // look for screensavers and powersave mode
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:     // screensaver trying to start
				case SC_MONITORPOWER:   // monitor going to powersave mode
					// returning 0 prevents either from happening
					return 0;
				default:
					break;
			}
		} break;

		case WM_COMMAND:	// Handle messages from the Menu bar
		{
			// Get a handle to the menu
			HMENU hMenu = ::GetMenu(hwnd);
			switch (LOWORD(wParam))
			{
				case ID_FILE_QUIT: // Activate the line DDA menu item
				{
					// send WM_QUIT to message queue
					PostQuitMessage(0);
					return 0;
				}
			}
			return 0;
		}

		case WM_CLOSE:    // window is being closed
		{
			// send WM_QUIT to message queue
			PostQuitMessage(0);
			return 0;
		}

		case WM_SIZE:
		{
			// update perspective with new width and height
			//Resize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}

		case WM_LBUTTONDOWN:
		{
			//MouseClicked(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}

        case WM_MOUSEMOVE:        // mouse movement
        {
            // Retrieve mouse screen position
            int x = (short)LOWORD(lParam);
            int y = (short)HIWORD(lParam);

            // Check to see if the left button is held down:
            bool leftButtonDown = wParam & MK_LBUTTON;

            // Check if right button down:
            bool rightButtonDown = wParam & MK_RBUTTON;
            //std::cout << x << ":" << y << std::endl;
        }

		//case WM_CHAR:             // key pressed
        //{}

		default:
			break;
	}

	return (DefWindowProc(hwnd, message, wParam, lParam));
}