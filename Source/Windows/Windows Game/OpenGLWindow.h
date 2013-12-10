#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW

#include <string>
#include <Windows.h>
#include "GL/gl.h"

//The OpenGL window class. It wraps the HANDLE of the window and initializes the openGL 
//rendering context. It is also in charge of processing the different event messages.
class OpenGLWindow
{
public:
	OpenGLWindow(const char* aTitle, int width, int weight, bool fullScreen);
	~OpenGLWindow();

	int width();
	int height();
	void swapBuffers();

private:
	//Register the window class with the correct window procedure (OnEvent)
	void registerWindowClass(const char* className);

	//Create the rendering context used by OpenGL
	void createOpenGLContext();

	//Called when a WM_SIZE message is received
	void resize(GLsizei width, GLsizei height);

	//Static function which will be the window procedure callback
  static LRESULT CALLBACK eventHandler(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);

	//Processes the messages that were received in OnEvent.
	void processEvent(UINT Message, WPARAM wParam, LPARAM lParam);

	//Member Variables
	HWND m_WindowHandle;
  HDC m_WindowDeviceContext;
  HGLRC m_OpenGLContext;    
	bool m_IsFullScreen;
	int m_WindowWidth;
	int m_WindowHeight;
	std::string m_ClassName;

	int m_LastMouseX;
	int m_LastMouseY;
};

#endif