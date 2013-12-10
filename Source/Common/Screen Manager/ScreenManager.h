#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <iostream>
#include <vector>

class Screen;

class ScreenManager
{
public:
	static ScreenManager* getInstance();
	static void cleanupInstance();
	
    void setScreenSize(float width, float height);
    float getScreenWidth();
    float getScreenHeight();
    
	void update(double delta);
	void paint();
    
	void addScreen(Screen* screen);
    
	void switchScreen(Screen* screen);
	void switchScreen(const char* name);
    
	Screen* getCurrentScreen();
	Screen* getScreenForName(const char* name);

	const char* getPreviousScreen();
    
private:
	ScreenManager();
	~ScreenManager();
    
	void loadScreens();
    
	static ScreenManager* s_Instance;
    
	std::vector<Screen*> m_Screens;
	Screen* m_CurrentScreen;
	Screen* m_PreviousScreen;
    
    float m_ScreenWidth;
    float m_ScreenHeight;
	bool m_ScreensLoaded;
};

#endif