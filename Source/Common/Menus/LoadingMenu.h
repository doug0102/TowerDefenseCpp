//
// LoadingMenu.h
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Menu.h"

class Level;

class LoadingMenu : public Menu
{
public:
	LoadingMenu();
	~LoadingMenu();

	// Returns the name of the screen
	const char* getName();

private:
	void buttonAction(UIButton* button);

	// Used to load/save levels
	Level* m_Level;
};