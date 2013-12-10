// GameOverMenu.h
// This class creates a screen which is used for a game over state within the game
// From this screen the player will be able to reset the level, return to the main menu, or exit 

#include "Menu.h"

class GameOverMenu : public Menu
{
public:
	GameOverMenu();
	~GameOverMenu();

	const char* getName();

private:
	void buttonAction(UIButton* button);
};