#ifndef WIN32_GAME_H
#define WIN32_GAME_H

#include <windows.h>

// The application class, which simply wraps the message queue and process
// the command line.
class Win32Game
{
public:
	Win32Game(HINSTANCE handleInstance);
	~Win32Game();

	// Creates the main window and start the message loop.
	void run();

private:
	HINSTANCE m_HandleInstance;
	bool m_IsFullScreen;
};

#endif