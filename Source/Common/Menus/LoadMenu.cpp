#include "LoadMenu.h"
#include "../UI/UIButton.h"
#include "../Game/Game.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"

LoadMenu::LoadMenu() : Menu(NULL, NULL)
{
	addButton(new UIButton("ButtonExit"));
}

LoadMenu::~LoadMenu()
{

}

const char* LoadMenu::getName()
{
    return LOAD_MENU_SCREEN_NAME;
}

// change for loading levels
// 6 slots
void LoadMenu::buttonAction(UIButton* button)
{
	
    int index = getIndexForButton(button);
    if(index == 0)
    {
		// Go back to the main menu
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
    }
	
}