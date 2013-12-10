#include "Logger.h"

#if WIN32
#include <windows.h>
#include <io.h>
#endif

#include <stdio.h>
#include <stdarg.h>

#define OUTPUT_BUFFER 512

bool Log::s_IsConsoleAllocated = false;
void Log::createConsole()
{
#if WIN32
	//Set the console allocated flag to 'true'
	s_IsConsoleAllocated = true;
    
	//Allocate the console window and set the window title.
	AllocConsole();
    
#if UNICODE
	SetConsoleTitle(L"Output Logger");
#else
	SetConsoleTitle("Output Logger");
#endif
    
	//Redirect unbuffered STDOUT to the console window.
	int hConHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 0x4000);
	FILE *filePointer = _fdopen(hConHandle, "w");
	*stdout = *filePointer;
	setvbuf(stdout, NULL, _IONBF, 0);
#endif
}

void Log::output(const char* output, ...)
{
#if DEBUG || _DEBUG
	//If the console isn't allocated, then allocate it.
	if(s_IsConsoleAllocated == false)
	{
		Log::createConsole();
	}
    
    //Create the output argument list and output it to the console.
    va_list arguments;
    va_start(arguments, output);
    vprintf (output, arguments);
    va_end (arguments);
#endif
}

void Log::error(const char* output, ...)
{
	char outputBuffer[OUTPUT_BUFFER];
    va_list arguments;
    va_start(arguments, output);
    vsprintf(outputBuffer, output, arguments);
    Log::output("%s - %s\n", "[ERROR]", outputBuffer);
    va_end (arguments);
}

void Log::trace(const char* output, ...)
{
	char outputBuffer[OUTPUT_BUFFER];
    va_list arguments;
    va_start(arguments, output);
    vsprintf(outputBuffer, output, arguments);
    Log::output("%s - %s\n", "[TRACE]", outputBuffer);
    va_end (arguments);
}

void Log::debug(const char* output, ...)
{
	char outputBuffer[OUTPUT_BUFFER];
    va_list arguments;
    va_start(arguments, output);
    vsprintf(outputBuffer, output, arguments);
    Log::output("%s - %s\n", "[DEBUG]", outputBuffer);
    va_end (arguments);
}