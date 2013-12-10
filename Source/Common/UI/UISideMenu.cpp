//
//  UISideMenu.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "UISideMenu.h"
#include "../Screen Manager/ScreenManager.h"
#include "../Input/Input.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"

 
UISideMenu::UISideMenu(UISideMenuListener* listener, SideMenuOrientation orientation) :
    m_Listener(listener),
    m_State(SideMenuClosed),
    m_Orientation(orientation),
    m_BackgroundColor(OpenGLColorRGBA(0.0f, 0.0f, 0.0f, 0.7f)),
    m_TargetX(0.0f),
    m_X(0.0f),
    m_Y(0.0f),
    m_Width(ScreenManager::getInstance()->getScreenWidth() * 0.125f),
    m_Height(ScreenManager::getInstance()->getScreenHeight()),
    m_SelectedButtonIndex(-1),
	m_FinishedAnimating(true)
{
    setState(SideMenuClosed);
}

UISideMenu::~UISideMenu()
{
    clearButtons();
}

void UISideMenu::update(double delta)
{
    //
    if(m_TargetX != m_X)
    {
        //
        float direction = fabsf(m_TargetX - m_X) / (m_TargetX - m_X);

        //
        m_X += UI_SIDE_MENU_SPEED * direction * delta;
        
        //
        if(direction == -1.0f)
        {
            if(m_X <= m_TargetX)
            {
                if(m_State == SideMenuOpening)
                {
                    setState(SideMenuOpen);
					m_FinishedAnimating = true;
                }
                else if(m_State == SideMenuClosing)
                {
                    setState(SideMenuClosed);
					m_FinishedAnimating = true;
                }
            }
        }
        else
        {
            if(m_X >= m_TargetX)
            {
                if(m_State == SideMenuOpening)
                {
                    setState(SideMenuOpen);
					m_FinishedAnimating = true;
                }
                else if(m_State == SideMenuClosing)
                {
                    setState(SideMenuClosed);
					m_FinishedAnimating = true;
                }
            }
        }
    
        //
        float centerX = m_X + (m_Width / 2.0f);
        for(int i = 0; i < m_Buttons.size(); i++)
        {
            m_Buttons.at(i)->setCenterX(centerX);
        }
    }
}

void UISideMenu::paint()
{
    OpenGLRenderer::getInstance()->setForegroundColor(m_BackgroundColor);
    OpenGLRenderer::getInstance()->drawRectangle(m_X, m_Y, m_Width, m_Height);
    
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons.at(i)->paint();
    }
}

void UISideMenu::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons.at(i)->mouseMovementEvent(positionX, positionY);
    }
}

void UISideMenu::mouseLeftClickUpEvent(float positionX, float positionY)
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons.at(i)->mouseLeftClickUpEvent(positionX, positionY);
    }
}
    
void UISideMenu::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_UP_ARROW)
    {
        if(m_SelectedButtonIndex != -1)
        {
            //
            m_Buttons.at(m_SelectedButtonIndex)->setIsSelected(false);
            
            //
            m_SelectedButtonIndex--;
            if(m_SelectedButtonIndex < 0)
            {
                m_SelectedButtonIndex = 0;
            }
            
            //
            m_Buttons.at(m_SelectedButtonIndex)->setIsSelected(true);
        }
    }
    else if (keyCode == KEYCODE_DOWN_ARROW)
    {
        if(m_SelectedButtonIndex != -1)
        {
            //
            m_Buttons.at(m_SelectedButtonIndex)->setIsSelected(false);
            
            //
            m_SelectedButtonIndex++;
            if(m_SelectedButtonIndex >= m_Buttons.size())
            {
                m_SelectedButtonIndex = m_Buttons.size() - 1;
            }
            
            //
            m_Buttons.at(m_SelectedButtonIndex)->setIsSelected(true);
        }
    }
    else
    {
        for(int i = 0; i < m_Buttons.size(); i++)
        {
            m_Buttons.at(i)->keyUpEvent(keyCode);
        }
    }
}

void UISideMenu::show()
{
    setState(SideMenuOpening);
	m_FinishedAnimating = false;
}

void UISideMenu::hide()
{
    setState(SideMenuClosing);
	m_FinishedAnimating = false;
}

bool UISideMenu::isShowing()
{
    return m_State == SideMenuOpen || m_State == SideMenuOpening;
}

void UISideMenu::addButton(UIButton* button)
{
    if(button != NULL)
    {
        //
        button->setListener(this);
        
        //
        m_Buttons.push_back(button);
        
        //
        float buttonsHeight = 0.0f;
        float maxButtonHeight = 0.0f;
        for(int i = 0; i < m_Buttons.size(); i++)
        {
            buttonsHeight += m_Buttons.at(i)->getHeight();
            maxButtonHeight = fmaxf(maxButtonHeight, m_Buttons.at(i)->getHeight());
        }
        
        //
        float heightNeeded = m_Height - buttonsHeight;
        float maxSpacer = 32.0f;
        float spacer = fminf(maxSpacer, heightNeeded / (m_Buttons.size() + 1));
        heightNeeded = m_Height - buttonsHeight - (spacer * (m_Buttons.size() + 1));
        float centerX = m_X + (m_Width / 2.0f);
        float centerY = heightNeeded / 2.0f + maxButtonHeight / 2.0f + spacer;
        
        //
        for(int i = 0; i < m_Buttons.size(); i++)
        {
            m_Buttons.at(i)->setCenterPosition(centerX, centerY);
            centerY += m_Buttons.at(i)->getHeight() + spacer;
        }
    }
}

int UISideMenu::getIndexForButton(UIButton* button)
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        if(m_Buttons.at(i) == button)
        {
            return i;
        }
    }
    return -1;
}

UIButton* UISideMenu::getButtonForIndex(int index)
{
    if(index >= 0 && index < m_Buttons.size())
    {
        return m_Buttons.at(index);
    }

    return NULL;
}

void UISideMenu::clearButtons()
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        delete m_Buttons.at(i);
        m_Buttons.at(i) = NULL;
    }
    
    m_Buttons.clear();
}

void UISideMenu::setState(SideMenuState state)
{
    m_State = state;
    
    switch (m_State)
    {
        case SideMenuClosed:
        m_X = (m_Orientation == SideMenuLeft ? -m_Width : ScreenManager::getInstance()->getScreenWidth());
        m_TargetX = m_X;
        break;
        
        case SideMenuClosing:
        m_TargetX = (m_Orientation == SideMenuLeft ? -m_Width : ScreenManager::getInstance()->getScreenWidth());
        break;
        
        case SideMenuOpen:
        m_X = (m_Orientation == SideMenuLeft ? 0.0f : ScreenManager::getInstance()->getScreenWidth() - m_Width);
        m_TargetX = m_X;
        break;
        
        case SideMenuOpening:
        m_TargetX = (m_Orientation == SideMenuLeft ? 0.0f : ScreenManager::getInstance()->getScreenWidth() - m_Width);
        break;
    }
}

void UISideMenu::buttonAction(UIButton* button)
{
    if(m_Listener != NULL)
    {
        m_Listener->sideMenuButtonAction(this, button, getIndexForButton(button));
    }
}

void UISideMenu::buttonIsSelected(UIButton* button)
{

}

bool UISideMenu::buttonShouldBeDeselectedOnExit(UIButton* button)
{
    return true;
}

void UISideMenu::buttonWasToggled(UIToggle* toggle)
{
    if(m_Listener != NULL)
    {
        m_Listener->sideMenuToggleAction(this, toggle, getIndexForButton(toggle));
    }
}




