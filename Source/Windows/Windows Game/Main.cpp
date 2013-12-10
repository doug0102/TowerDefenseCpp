#include "Win32Game.h" 
#include "Win32Exception.h"

int WINAPI WinMain(HINSTANCE aCurrentInstance, HINSTANCE aPreviousInstance, LPSTR aCommandLine, int aCommandShow)
{
	try
	{
		//Create the WindowsGame class, parse the command line and start the game.
		Win32Game game(aCurrentInstance);
		game.run();
	}
	catch(Win32Exception& exception)
	{
		MessageBox(NULL, exception.errorString(), "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	return 0;
}