//
//  UIToggle.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "UIToggle.h"
#include "../OpenGL/OpenGL.h"
#include "../Input/Input.h"


UIToggle::UIToggle(const char* textureFile) : UIButton(textureFile),
    m_ToggledState(NULL),
    m_IsToggled(false)
{
    //There should be a large texture of the same name with
    //'-Toggled' appended to it for the selected state
    std::string toggledTextureFile = std::string(textureFile);
    toggledTextureFile += "-Toggled";
    
    //Create the selected state texture object
    m_ToggledState = new OpenGLTexture(toggledTextureFile.c_str());
}

UIToggle::~UIToggle()
{
    if(m_ToggledState != NULL)
    {
        delete m_ToggledState;
        m_ToggledState = NULL;
    }
}

void UIToggle::paint()
{
    if(isToggled() == true)
    {
        float x = m_CenterPositionX - m_ToggledState->getSourceWidth() / 2.0f;
        float y = m_CenterPositionY - m_ToggledState->getSourceHeight() / 2.0f;
        OpenGLRenderer::getInstance()->drawTexture(m_ToggledState, x, y);
    }
    else
    {
        UIButton::paint();
    }
}

bool UIToggle::isToggled()
{
    return m_IsToggled;
}

void UIToggle::setIsToggled(bool isToggled)
{
    m_IsToggled = isToggled;
}

void UIToggle::mouseLeftClickUpEvent(float positionX, float positionY)
{
    float left = m_CenterPositionX - m_SelectedState->getSourceWidth() / 2.0f;
    float right = m_CenterPositionX + m_SelectedState->getSourceWidth() / 2.0f;
    float top = m_CenterPositionY - m_SelectedState->getSourceHeight() / 2.0f;
    float bottom = m_CenterPositionY + m_SelectedState->getSourceHeight() / 2.0f;
    
    if(positionX >= left && positionX <= right && positionY >= top && positionY <= bottom)
    {
        //
        setIsToggled(!isToggled());
    
        //
        if(m_Listener != NULL)
        {
            ((UIToggleListener*)m_Listener)->buttonWasToggled(this);
        }
    }
}

void UIToggle::keyUpEvent(int keyCode)
{
    if(m_IsSelected == true)
    {
        if(keyCode == KEYCODE_RETURN)
        {
            if(m_Listener != NULL)
            {
                ((UIToggleListener*)m_Listener)->buttonWasToggled(this);
            }
        }
    }
}