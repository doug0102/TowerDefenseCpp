#include "LoadingMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../OpenGL/OpenGL.h"

LoadingMenu::LoadingMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("Tile1"));
	addButton(new UIButton("Tile2"));
	addButton(new UIButton("Tile3"));
	addButton(new UIButton("Tile4"));
	addButton(new UIButton("Tile5"));
	addButton(new UIButton("Tile6"));

	addButton(new UIButton("ButtonExit"));

	m_Level = new Level(true);

	
	m_Background = new OpenGLTexture("LoadBG");
}

LoadingMenu::~LoadingMenu()
{
	if(m_Level != NULL)
	{
		delete m_Level;
		m_Level = NULL;
	}
}

const char* LoadingMenu::getName()
{
	return LOAD_MENU_SCREEN_NAME;
}

void LoadingMenu::buttonAction(UIButton* button)
{
	switch(getIndexForButton(button))
	{
	case 0:
		m_Level->load("save0.txt");
		break;
	case 1:
		m_Level->load("save1.txt");
		break;
	case 2:
		m_Level->load("save2.txt");
		break;
	case 3:
		m_Level->load("save3.txt");
		break;
	case 4:
		m_Level->load("save4.txt");
		break;
	case 5 :
		m_Level->load("save5.txt");
		break;
	case 6:
		ScreenManager::getInstance()->switchScreen(ScreenManager::getInstance()->getPreviousScreen());
		return;
	}

	m_Level->save("TempLoad.txt");


	if(ScreenManager::getInstance()->getPreviousScreen() == LEVEL_EDITOR_SCREEN_NAME)
	{
		// The load menu was called from the level editor, load the desired level into the level editor 
		ScreenManager::getInstance()->getScreenForName(LEVEL_EDITOR_SCREEN_NAME)->keyUpEvent(KEYCODE_P);
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else
	{
		// Calls the keyUpEvent to load the level and switches to the game screen
		ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME)->keyUpEvent(KEYCODE_P);
		ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
	}
}