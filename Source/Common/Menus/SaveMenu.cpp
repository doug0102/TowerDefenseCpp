#include "SaveMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../OpenGL/OpenGL.h"

SaveMenu::SaveMenu() : Menu(NULL, NULL)

{
	addButton(new UIButton("Tile1"));
	addButton(new UIButton("Tile2"));
	addButton(new UIButton("Tile3"));
	addButton(new UIButton("Tile4"));
	addButton(new UIButton("Tile5"));
	addButton(new UIButton("Tile6"));

	addButton(new UIButton("ButtonExit"));

	m_Level = new Level(true);

	m_Background = new OpenGLTexture("SaveBG");
}

SaveMenu::~SaveMenu()
{
	if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
}

const char* SaveMenu::getName()
{
    return SAVE_MENU_SCREEN_NAME;
}

// saving up to 6 levels
// 6 slots
void SaveMenu::buttonAction(UIButton* button)
{
	// Load the temporary save form the level editor
	m_Level->load("TempSave.txt");
    int index = getIndexForButton(button);

	// Make a copy of the temporary save dependant on the button selected
	if(index == 0)
	{
		m_Level->save("save0.txt");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else if(index == 1)
	{
		m_Level->save("save1.txt");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else if(index == 2)
	{
		m_Level->save("save2.txt");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else if(index == 3)
	{
		m_Level->save("save3.txt");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else if(index == 4)
	{
		m_Level->save("save4.txt");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else if(index == 5)
	{
		m_Level->save("save5.txt");
		ScreenManager::getInstance()->switchScreen(LEVEL_EDITOR_SCREEN_NAME);
	}
	else if(index == 6)
    {
		// Go back to the previous screen
        ScreenManager::getInstance()->switchScreen(ScreenManager::getInstance()->getPreviousScreen());
    }
	
}