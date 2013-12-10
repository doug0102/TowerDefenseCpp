//
//  UISideMenu.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__UISideMenu__
#define __GAM_1514_OSX_Game__UISideMenu__

#include "UIToggle.h"
#include "../OpenGL/OpenGL.h"
#include <stdlib.h>
#include <vector>

enum SideMenuOrientation
{
    SideMenuLeft = 0,
    SideMenuRight
};

class UISideMenuListener;

class UISideMenu : public UIToggleListener
{
public:
    UISideMenu(UISideMenuListener* listener, SideMenuOrientation orientation);
    ~UISideMenu();
    
    void update(double delta);
    void paint();
    
    void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void keyUpEvent(int keyCode);
    
    void show();
    void hide();
    bool isShowing();
    
    void addButton(UIButton* button);
    int getIndexForButton(UIButton* button);
    UIButton* getButtonForIndex(int index);
    void clearButtons();
    
protected:

	friend class Game;

    enum SideMenuState
    {
        SideMenuClosed = 0,
        SideMenuClosing,
        SideMenuOpen,
        SideMenuOpening
    };
    void setState(SideMenuState state);
    
    void buttonAction(UIButton* button);
    void buttonIsSelected(UIButton* button);
    bool buttonShouldBeDeselectedOnExit(UIButton* button);
    void buttonWasToggled(UIToggle* button);
    
    UISideMenuListener* m_Listener;
    
    SideMenuState m_State;
    SideMenuOrientation m_Orientation;
    
    OpenGLColor m_BackgroundColor;
    
    float m_TargetX;
    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;
    
    std::vector<UIButton*> m_Buttons;
    int m_SelectedButtonIndex;

	bool m_FinishedAnimating;
};


class UISideMenuListener
{
public:
    virtual void sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex) {};
    virtual void sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex) {};
};

#endif /* defined(__GAM_1514_OSX_Game__UISideMenu__) */
