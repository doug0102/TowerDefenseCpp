#ifndef LOGGER_H
#define LOGGER_H

class Log
{
public:
	static void error(const char* output, ...);
	static void trace(const char* output, ...);
	static void debug(const char* output, ...);

private:
	static void createConsole();
	static void output(const char* output, ...);
	static bool s_IsConsoleAllocated;
};

#endif
