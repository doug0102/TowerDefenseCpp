//
//  LoadMenu.h
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Menu.h"

class LoadMenu : public Menu
{
public:
    LoadMenu();
    ~LoadMenu();
    
    const char* getName();

private:
    void buttonAction(UIButton* button);
};