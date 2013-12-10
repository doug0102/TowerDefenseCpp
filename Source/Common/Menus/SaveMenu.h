//
//  SaveMenu.h
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Menu.h"

class Level;

class SaveMenu : public Menu
{
public:
    SaveMenu();
    ~SaveMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);

	Level* m_Level;
};