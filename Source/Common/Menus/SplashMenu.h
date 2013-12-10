
#include "Menu.h"

class SplashMenu : public Menu
{
public:
	SplashMenu();
	~SplashMenu();

	// Returns the name of the screen
	const char* getName(); 

private:
    void buttonAction(UIButton* button);
};