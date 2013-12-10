#include "SplashMenu.h"
#include "../UI/UIButton.h"
#include "../Screen Manager/ScreenManager.h"

SplashMenu::SplashMenu() : Menu (NULL, NULL)
{
	addButton(new UIButton("ButtonSplash"));
}

SplashMenu::~SplashMenu()
{

}

const char* SplashMenu::getName()
{
	return SPLASH_SCREEN_NAME;
}

void SplashMenu::buttonAction(UIButton* button)
{
	switch(getIndexForButton(button))
	{
	case 0:
		ScreenManager::getInstance()->switchScreen(ScreenManager::getInstance()->getScreenForName(MAIN_MENU_SCREEN_NAME));
		break;
	}
}