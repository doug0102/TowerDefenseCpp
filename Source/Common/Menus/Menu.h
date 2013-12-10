//
//  Menu.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__Menu__
#define __GAM_1514_OSX_Game__Menu__

#include "../Screen Manager/Screen.h"
#include "../Constants/Constants.h"
#include "../UI/UIButton.h"
#include <stdlib.h>
#include <vector>


class OpenGLTexture;

class Menu : public Screen, public UIButtonListener
{
public:
    Menu(const char* background, const char* title, bool showBack = false);
    virtual ~Menu();
    
    virtual const char* getName() = 0;

    virtual void update(double delta);
    virtual void paint();
    
    virtual void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    virtual void mouseLeftClickUpEvent(float positionX, float positionY);
    
    virtual void keyUpEvent(int keyCode);
    
protected:
    virtual void addButton(UIButton* button);
    virtual int getIndexForButton(UIButton* button);
    virtual void clearButtons();
    
    virtual void buttonIsSelected(UIButton* button);
    virtual void buttonAction(UIButton* button);
    

    OpenGLTexture* m_Background;
    OpenGLTexture* m_Title;
    
    float m_TitleX;
    float m_TitleY;
    int m_SelectedIndex;
    bool m_ShowBack;
    std::vector<UIButton*> m_Buttons;
};

#endif /* defined(__GAM_1514_OSX_Game__Menu__) */
