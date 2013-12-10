// CompleteMenu.h
// This class is used to create a menu to be displayed to the player upon level completion
// Allows the player to reset the level, return to the main menu, or exit the game

#include "Menu.h"

class CompleteMenu : public Menu
{
public:
	CompleteMenu();
	~CompleteMenu();

	const char* getName();

private:
	void buttonAction(UIButton* button);

};
