#include "Win32Game.h"
#include "OpenGLWindow.h"
#include "../../Common/OpenGL/OpenGLRenderer.h"
#include "../../Common/Constants/Constants.h"
#include "../../Common/Utils/Utils.h"
#include "../../Common/Input/InputManager.h"
#include "../../Common/Screen Manager/ScreenManager.h"
#include <string>

Win32Game::Win32Game(HINSTANCE aHandleInstance) :
  m_HandleInstance(aHandleInstance), 
  m_IsFullScreen(false)
{

}

Win32Game::~Win32Game()
{

}

void Win32Game::run()
{
	//Create the OpenGL window
	OpenGLWindow openGLWindow(WINDOW_TITLE, WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, WINDOW_IS_FULLSCREEN);

	//Get the frames per second and calculate the frame time in milleseconds
	unsigned long frameTime = (unsigned long)((1.0 / (double)FRAMES_PER_SECOND) * 1000.0);

	//Cache the last tick count, and calculate the next tick count.
	unsigned long lastTickCount = GetTickCount();
	unsigned long nextTickCount = GetTickCount() + frameTime;
	unsigned long sleepTime = frameTime;
	bool canUpdate = false;

	//Loop until a WM_QUIT message is received
	MSG Message;
    Message.message = ~WM_QUIT;
    while(Message.message != WM_QUIT)
    {
		//Wait until a message comes in or until the timeout expires. The timeout is 
		//recalculated so that this function will return at least every FRAME_TIME msec.
		DWORD dwResult = MsgWaitForMultipleObjectsEx(0, NULL, sleepTime, QS_ALLEVENTS, 0);
		if(dwResult != WAIT_TIMEOUT)
		{
			//If the function returned with no timeout, it means that at least one message has been received, so process all of them.
			while(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			{
				// If a message was waiting in the message queue, process it
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

			//If the current time is close (or past) to the next tick count, the game should be processed.
			if(GetTickCount() >= nextTickCount)
			{
				canUpdate = true;
			}
			else
			{
				canUpdate = false;
			}
		}
		else
		{
			//On a timeout, the game should be processed.
			canUpdate = true;
		}

		//Check if the game should be processed
		if(canUpdate == true)
		{
			//Get the current tick count, and calculate the current delta time.
			unsigned long currentTickCount = GetTickCount();
			double deltaTime = (currentTickCount - lastTickCount) / 1000.0;
			
      //Process the input events
      InputManager::getInstance()->processInputEvents();

			//Update the Game with the delta time.
			ScreenManager::getInstance()->update(deltaTime);

			//Clear the OpenGL buffers
			OpenGLRenderer::getInstance()->clear();

			//Paint the Game.
			ScreenManager::getInstance()->paint();

			//Swap the OpenGL window's buffer
			openGLWindow.swapBuffers();

			//Cache the current tick count and calculate the next tick count.
			lastTickCount = currentTickCount;
			nextTickCount = nextTickCount + frameTime;
		}

		//Calculate the sleep time, which is the difference between the current 
		//time and the next tick count.
		sleepTime =  nextTickCount - GetCurrentTime();

		//If the sleep time is larger than the frame time, it probably means that 
		//the processing was stopped, recalculate the next tick count.
		if(sleepTime > frameTime)
		{
			sleepTime = frameTime;
			nextTickCount = GetCurrentTime() + frameTime;
		}
	}

	//
	ScreenManager::cleanupInstance();
}