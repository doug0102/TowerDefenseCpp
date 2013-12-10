//
//  UIToggle.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__UIToggle__
#define __GAM_1514_OSX_Game__UIToggle__

#include "UIButton.h"

class UIToggleListener;

class UIToggle : public UIButton
{
public:
    UIToggle(const char* textureFile);
    virtual ~UIToggle();
    
    void paint();
    
    bool isToggled();
    void setIsToggled(bool isToggled);
    
    void mouseLeftClickUpEvent(float positionX, float positionY);
    
    void keyUpEvent(int keyCode);
    
private:
    OpenGLTexture* m_ToggledState;
    bool m_IsToggled;
};

class UIToggleListener : public UIButtonListener
{
public:
    virtual void buttonAction(UIButton* button) = 0;
    virtual void buttonIsSelected(UIButton* button) = 0;
    virtual void buttonWasToggled(UIToggle* button) = 0;
};

#endif /* defined(__GAM_1514_OSX_Game__UIToggle__) */
