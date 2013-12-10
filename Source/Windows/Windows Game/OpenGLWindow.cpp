#include "OpenGLWindow.h"
#include "../../Common/OpenGL/OpenGLRenderer.h"
#include "../../Common/Constants/Constants.h"
#include "../../Common/Input/InputManager.h"
#include "../../Common/Screen Manager/ScreenManager.h"
#include "Win32Exception.h"
#include <WindowsX.h>


OpenGLWindow::OpenGLWindow(const char* aTitle, int aWidth, int aHeight, bool aIsFullScreen) :  
	m_WindowHandle(NULL), 
	m_WindowDeviceContext(NULL),
	m_OpenGLContext(NULL), 
    m_IsFullScreen(aIsFullScreen)
{
	//Pass in the window title, and register the window class.
	registerWindowClass(aTitle);

	//
	RECT WindowRect;
	WindowRect.top = WindowRect.left = 0;
	WindowRect.right = aWidth;
	WindowRect.bottom = aHeight;

	//Window Extended Style
	DWORD extendedWindowStyle = 0;	

	//Windows Style
	DWORD windowStyle = 0;		

	//Do we hide the cursor?
	ShowCursor(WINDOW_SHOW_MOUSE_CURSOR);

	if(m_IsFullScreen == true)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		
		dmScreenSettings.dmPelsWidth = aWidth;			
		dmScreenSettings.dmPelsHeight = aHeight;		
		dmScreenSettings.dmBitsPerPel = 32;		
		dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		//Change the display settings to fullscreen. On error, throw an exception.
		if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			throw Win32Exception("Unable to swith to fullscreen mode");
		}

		extendedWindowStyle = WS_EX_APPWINDOW;	
		windowStyle = WS_POPUP;	
	}
	else
	{
		extendedWindowStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		windowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX;
	}

	//Adjust the window to the true requested size
	AdjustWindowRectEx(&WindowRect, windowStyle, false, extendedWindowStyle);	

	//Now create the OpenGL window
    m_WindowHandle = CreateWindowEx(extendedWindowStyle, 
							 aTitle, 
							 aTitle, 
							 WS_CLIPSIBLINGS | WS_CLIPCHILDREN | windowStyle,
							 WINDOW_DEFAULT_X, WINDOW_DEFAULT_Y, 
							 WindowRect.right - WindowRect.left, 
							 WindowRect.bottom - WindowRect.top, 
							 NULL, NULL, 
							 GetModuleHandle(NULL), 
							 this);

	//
	if(m_WindowHandle == NULL)
	{
		throw Win32Exception("Cannot create the main window");
	}

	//
	createOpenGLContext();

	//Show the newly created window
	ShowWindow(m_WindowHandle, SW_SHOW);

	// Call OnSize manually because in fullscreen mode it will be 
	// called only when the window is created (which is too early
	// because OpenGL is not initialized yet).
	resize(aWidth, aHeight);

	//
	m_LastMouseX = -1;
	m_LastMouseY = -1;
}

OpenGLWindow::~OpenGLWindow()
{
	//Remove the full screen setting and show the cursor
	if(m_IsFullScreen == true)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);	
	}

	//
	if(m_OpenGLContext != NULL)
	{
		//Make the rendering context not current
		wglMakeCurrent(NULL, NULL);

		//Delete the OpenGL rendering context
		wglDeleteContext(m_OpenGLContext);
		m_OpenGLContext = NULL;
	}

	//Release the window device context
	if(m_WindowDeviceContext != NULL)
	{
		ReleaseDC(m_WindowHandle, m_WindowDeviceContext);
		m_WindowDeviceContext = NULL;
	}

	//Finally, destroy the OpenGL window and unregister the window class.
    DestroyWindow(m_WindowHandle);
    UnregisterClass(m_ClassName.c_str(), GetModuleHandle(NULL));
}

LRESULT OpenGLWindow::eventHandler(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_NCCREATE)
	{
        //Get the creation parameters.
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

        //Set as the "user data" parameter of the window
        SetWindowLongPtr(Handle, GWLP_USERDATA, reinterpret_cast<long>(pCreateStruct->lpCreateParams));
	}

    //Get the CMainWindow instance corresponding to the window handle
    OpenGLWindow* openGLWindow = reinterpret_cast<OpenGLWindow*>(GetWindowLongPtr(Handle, GWLP_USERDATA));
	if (openGLWindow != NULL)
	{
		openGLWindow->processEvent(Message, wParam, lParam);
	}

    return DefWindowProc(Handle, Message, wParam, lParam);
}

void OpenGLWindow::processEvent(UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
    switch(aMessage)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
			break;

		case WM_SIZE:
			resize(LOWORD(aLParam), HIWORD(aLParam));
			break;

    case WM_KEYDOWN:
      InputManager::getInstance()->handleKeyDown(aWParam);
			break;

		case WM_KEYUP:
			//if(aWParam == VK_ESCAPE)
			//{
			//	std::string message = "Are you sure you want to exit ";
			//	message.append(WINDOW_TITLE);
			//	message.append("?");
			//	if(WINDOW_IS_FULLSCREEN == true || MessageBox(NULL, message.c_str(), "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
			//	{
			//		exit(0);
			//	}
			//}
			//else
			{
				InputManager::getInstance()->handleKeyUp(aWParam);
			}
			break;

		case WM_MOUSEMOVE:
			{
				//
				int positionX = GET_X_LPARAM(aLParam);
				int positionY = GET_Y_LPARAM(aLParam);
		
				//
				if(m_LastMouseX != -1 && m_LastMouseY != -1)
				{
					int differenceX = positionX - m_LastMouseX;
					int differenceY = positionY - m_LastMouseY;
					InputManager::getInstance()->handleMouseMovement(differenceX, differenceY, positionX, positionY);
				}

				//
				m_LastMouseX = positionX;
				m_LastMouseY = positionY;
			}
			break;

		case WM_LBUTTONDOWN:
			{
				int positionX = GET_X_LPARAM(aLParam);
				int positionY = GET_Y_LPARAM(aLParam);
				InputManager::getInstance()->handleMouseLeftClickDown(positionX, positionY);
			}
			break;

		case WM_LBUTTONUP:
			{
				int positionX = GET_X_LPARAM(aLParam);
				int positionY = GET_Y_LPARAM(aLParam);
				InputManager::getInstance()->handleMouseLeftClickUp(positionX, positionY);
			}
			break;

		case WM_RBUTTONDOWN:
			{
				int positionX = GET_X_LPARAM(aLParam);
				int positionY = GET_Y_LPARAM(aLParam);
				InputManager::getInstance()->handleMouseRightClickDown(positionX, positionY);
			}
			break;

		case WM_RBUTTONUP:
			{
				int positionX = GET_X_LPARAM(aLParam);
				int positionY = GET_Y_LPARAM(aLParam);
				InputManager::getInstance()->handleMouseRightClickUp(positionX, positionY);
			}
            break;
    }
}

void OpenGLWindow::registerWindowClass(const char* aClassName)
{
	//Save the class name parameter, we will need 
	//it later to unregister the window.
	m_ClassName = std::string(aClassName);

	//Setup the window class
    WNDCLASS WindowClass;
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = &OpenGLWindow::eventHandler;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = GetModuleHandle(NULL);
    WindowClass.hIcon         = NULL;
    WindowClass.hCursor       = 0;
    WindowClass.hbrBackground = 0;
    WindowClass.lpszMenuName  = NULL;
    WindowClass.lpszClassName = m_ClassName.c_str();

	//Register the window class
    RegisterClass(&WindowClass);
}

void OpenGLWindow::createOpenGLContext()
{
	//Describes the pixel format of the drawing surface
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset(&pixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 32;

	//Create the window device context
	m_WindowDeviceContext = GetDC(m_WindowHandle);
	if (m_WindowDeviceContext == NULL)	
	{
		throw Win32Exception("Unable to create rendering context");
	}

	//Get the correct pixel format from the device context
	int pixelFormat = ChoosePixelFormat(m_WindowDeviceContext, &pixelFormatDescriptor);
	if(pixelFormat == 0)		
	{
		throw Win32Exception("Unable to create rendering context");
	}

	//Set the new pixel format
	if(SetPixelFormat(m_WindowDeviceContext, pixelFormat, &pixelFormatDescriptor) == false)	
	{
		throw Win32Exception("Unable to create rendering context");
	}

	//Create the OpenGL rendering context
	m_OpenGLContext = wglCreateContext(m_WindowDeviceContext);
	if (m_OpenGLContext == NULL)	
	{
		throw Win32Exception("Unable to create rendering context");
	}

	//Activate the OpenGL rendering context
	if(wglMakeCurrent(m_WindowDeviceContext, m_OpenGLContext) == false)
	{
		throw Win32Exception("Unable to create rendering context");		
	}
}

void OpenGLWindow::resize(GLsizei aWidth, GLsizei aHeight)
{
	//Set the window width and height variables
	m_WindowWidth = aWidth;
	m_WindowHeight = aHeight;
	
	//
	if(m_WindowDeviceContext != NULL)
	{
		//
		ScreenManager::getInstance()->setScreenSize(m_WindowWidth, m_WindowHeight);

		//Sets the size of the OpenGL viewport
		glViewport(0, 0, m_WindowWidth, m_WindowHeight);

		//Select the projection stack and apply an orthographic projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, m_WindowWidth, m_WindowHeight, 0.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
	}
}

int OpenGLWindow::width()
{
	return m_WindowWidth;
}

int OpenGLWindow::height()
{
	return m_WindowHeight;
}

void OpenGLWindow::swapBuffers()
{
	SwapBuffers(m_WindowDeviceContext);
}
