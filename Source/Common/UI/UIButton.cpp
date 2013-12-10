//
//  UIButton.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "UIButton.h"
#include "../OpenGL/OpenGL.h"
#include "../Input/Input.h"
#include <stdlib.h>
#include <string>


UIButton::UIButton(const char* textureFile, const char* overlayFile) :
    m_Listener(NULL),
    m_NormalState(NULL),
    m_SelectedState(NULL),
    m_Overlay(NULL),
    m_CenterPositionX(0.0f),
    m_CenterPositionY(0.0f),
    m_IsSelected(false)
{
    //Create the normal state texture object
    m_NormalState = OpenGLTextureCache::getInstance()->getTexture(textureFile);
    
    //There should be a large texture of the same name with
    //'-Highlighted' appended to it for the selected state
    std::string largeTextureFile = std::string(textureFile);
    largeTextureFile += "-Highlighted";
    
    //Create the selected state texture object
    m_SelectedState = OpenGLTextureCache::getInstance()->getTexture(largeTextureFile.c_str());
    
    //If there is an overlay image, create the texture
    if(overlayFile != NULL)
    {
        m_Overlay = OpenGLTextureCache::getInstance()->getTexture(overlayFile);
    }
}

UIButton::~UIButton()
{   
    m_NormalState = NULL;
    m_SelectedState = NULL;
    m_Overlay = NULL;
}

void UIButton::paint()
{
    if(m_IsSelected == true)
    {
        float x = m_CenterPositionX - m_SelectedState->getSourceWidth() / 2.0f;
        float y = m_CenterPositionY - m_SelectedState->getSourceHeight() / 2.0f;
        OpenGLRenderer::getInstance()->drawTexture(m_SelectedState, x, y);
    }
    else
    {
        float x = m_CenterPositionX - m_NormalState->getSourceWidth() / 2.0f;
        float y = m_CenterPositionY - m_NormalState->getSourceHeight() / 2.0f;
        OpenGLRenderer::getInstance()->drawTexture(m_NormalState, x, y);
    }
    
    if(m_Overlay != NULL)
    {
        float x = m_CenterPositionX - m_Overlay->getSourceWidth() / 2.0f;
        float y = m_CenterPositionY - m_Overlay->getSourceHeight() / 2.0f;
        OpenGLRenderer::getInstance()->drawTexture(m_Overlay, x, y);
    }
}

void UIButton::mouseMovementEvent(float positionX, float positionY)
{
    float left = m_CenterPositionX - m_SelectedState->getSourceWidth() / 2.0f;
    float right = m_CenterPositionX + m_SelectedState->getSourceWidth() / 2.0f;
    float top = m_CenterPositionY - m_SelectedState->getSourceHeight() / 2.0f;
    float bottom = m_CenterPositionY + m_SelectedState->getSourceHeight() / 2.0f;
    
    if(positionX >= left && positionX <= right && positionY >= top && positionY <= bottom)
    {
        setIsSelected(true);
        
        if(m_Listener != NULL)
        {
            m_Listener->buttonIsSelected(this);
        }
    }
    else
    {
        if(m_Listener != NULL)
        {
            if(m_Listener->buttonShouldBeDeselectedOnExit(this) == true)
            {
                setIsSelected(false);
            }
        }
    }
}

void UIButton::mouseLeftClickUpEvent(float positionX, float positionY)
{
    float left = m_CenterPositionX - m_SelectedState->getSourceWidth() / 2.0f;
    float right = m_CenterPositionX + m_SelectedState->getSourceWidth() / 2.0f;
    float top = m_CenterPositionY - m_SelectedState->getSourceHeight() / 2.0f;
    float bottom = m_CenterPositionY + m_SelectedState->getSourceHeight() / 2.0f;
    
    if(positionX >= left && positionX <= right && positionY >= top && positionY <= bottom)
    {
        if(m_Listener != NULL)
        {
            m_Listener->buttonAction(this);
        }
    }
}

void UIButton::keyUpEvent(int keyCode)
{
    if(m_IsSelected == true)
    {
        if(keyCode == KEYCODE_RETURN)
        {
            if(m_Listener != NULL)
            {
                m_Listener->buttonAction(this);
            }
        }
    }
}

void UIButton::setListener(UIButtonListener* listener)
{
    m_Listener = listener;
}

void UIButton::setCenterPosition(float centerX, float centerY)
{
    setCenterX(centerX);
    setCenterY(centerY);
}

void UIButton::setCenterX(float centerX)
{
    m_CenterPositionX = centerX;
}

void UIButton::setCenterY(float centerY)
{
    m_CenterPositionY = centerY;
}

void UIButton::setIsSelected(bool isSelected)
{
    m_IsSelected = isSelected;
}

void UIButton::swapOverlay(const char* overlayFile)
{
    //Check to see if the overlayFile is different from the current overlay
    if(strcmp(m_Overlay->getFilename().c_str(), overlayFile) == 0)
    {
        return;
    }
    
    //Get the new overlay texture
    m_Overlay = OpenGLTextureCache::getInstance()->getTexture(overlayFile);
}

float UIButton::getWidth()
{
    if(m_SelectedState != NULL)
    {
        return m_SelectedState->getSourceWidth();
    }
    
    return 0.0f;
}

float UIButton::getHeight()
{
    if(m_SelectedState != NULL)
    {
        return m_SelectedState->getSourceHeight();
    }
    
    return 0.0f;
}

void UIButton::changeButtonTexture(const char* textureFile)
{
	//Create the normal state texture object
    m_NormalState = OpenGLTextureCache::getInstance()->getTexture(textureFile);
    
    //There should be a large texture of the same name with
    //'-Highlighted' appended to it for the selected state
    std::string largeTextureFile = std::string(textureFile);
    largeTextureFile += "-Highlighted";
    
    //Create the selected state texture object
    m_SelectedState = OpenGLTextureCache::getInstance()->getTexture(largeTextureFile.c_str());
}
