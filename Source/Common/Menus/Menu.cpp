//
//  Menu.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Menu.h"
#include "../OpenGL/OpenGL.h"


Menu::Menu(const char* background, const char* title, bool showBack) :
    m_Background(NULL),
    m_Title(NULL),
    m_TitleX(0.0f),
    m_TitleY(0.0f),
    m_SelectedIndex(-1),
    m_ShowBack(showBack)
{
    //
    if(background != NULL)
    {
        m_Background = new OpenGLTexture(background);
    }
    
    //
    if(title != NULL)
    {
        //
        m_Title = new OpenGLTexture(title);
    
        //Calculate the title's x and y positions
        m_TitleX = (getWidth() - m_Title->getSourceWidth()) / 2.0f;
        m_TitleY = getHeight() * MENU_TITLE_Y_PERCENTAGE;
    }
}

Menu::~Menu()
{
    if(m_Background != NULL)
    {
        delete m_Background;
        m_Background = NULL;
    }
    
    if(m_Title != NULL)
    {
        delete m_Title;
        m_Title = NULL;
    }
    
    clearButtons();
}

void Menu::update(double delta)
{

}

void Menu::paint()
{
    if(m_Background != NULL)
    {
        OpenGLRenderer::getInstance()->drawTexture(m_Background, 0.0f, 0.0f);
    }
    else
    {
        OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlack());
        OpenGLRenderer::getInstance()->drawRectangle(0.0f, 0.0f, getWidth(), getHeight());
    }
    
    if(m_Title != NULL)
    {
        OpenGLRenderer::getInstance()->drawTexture(m_Title, m_TitleX, m_TitleY);
    }
    
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons.at(i)->paint();
    }
}

void Menu::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons.at(i)->mouseMovementEvent(positionX, positionY);
    }
}

void Menu::mouseLeftClickUpEvent(float positionX, float positionY)
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons.at(i)->mouseLeftClickUpEvent(positionX, positionY);
    }
}
    
void Menu::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_UP_ARROW)
    {
        if(m_SelectedIndex != -1)
        {
            //
            m_Buttons.at(m_SelectedIndex)->setIsSelected(false);
            
            //
            m_SelectedIndex--;
            if(m_SelectedIndex < 0)
            {
                m_SelectedIndex = 0;
            }
            
            //
            m_Buttons.at(m_SelectedIndex)->setIsSelected(true);
        }
    }
    else if (keyCode == KEYCODE_DOWN_ARROW)
    {
        if(m_SelectedIndex != -1)
        {
            //
            m_Buttons.at(m_SelectedIndex)->setIsSelected(false);
            
            //
            m_SelectedIndex++;
            if(m_SelectedIndex >= m_Buttons.size())
            {
                m_SelectedIndex = m_Buttons.size() - 1;
            }
            
            //
            m_Buttons.at(m_SelectedIndex)->setIsSelected(true);
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

void Menu::addButton(UIButton* button)
{
    if(button != NULL)
    {
        //
        int index = m_Buttons.size();
        
        //
        button->setListener(this);
        
        //
        if(index == 0)
        {
            button->setIsSelected(true);
            m_SelectedIndex = 0;
        }
        else if(index == 1 && m_ShowBack == true)
        {
            m_Buttons.at(m_SelectedIndex)->setIsSelected(false);
            button->setIsSelected(true);
            m_SelectedIndex = 1;
        }
        
        //
        m_Buttons.push_back(button);
        
        //
        float spacer = getHeight() * MENU_ITEMS_SPACER_PERCENTAGE;
        
        
        
        
        float startingY = (m_Title != NULL ? m_TitleY + m_Title->getSourceHeight() : 0.0f) + spacer;
        float availableHeight = getHeight() - startingY;
        float totalHeight = spacer * m_Buttons.size();
        if(m_ShowBack == true)
        {
            totalHeight -= spacer;
        }
        
        float centerX = getWidth() / 2.0f;
        float centerY = startingY + (availableHeight - totalHeight) / 2.0f;

        //
        for(int i = 0; i < m_Buttons.size(); i++)
        {
            if(i == 0 && m_ShowBack == true)
            {
                m_Buttons.at(i)->setCenterPosition(getWidth() * 0.08984375f, getHeight() * 0.1328125f);
            }
            else
            {
                m_Buttons.at(i)->setCenterPosition(centerX, centerY);
                centerY += spacer;
            }
        }
    }
}

int Menu::getIndexForButton(UIButton* button)
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

void Menu::clearButtons()
{
    for(int i = 0; i < m_Buttons.size(); i++)
    {
        delete m_Buttons.at(i);
        m_Buttons.at(i) = NULL;
    }
    
    m_Buttons.clear();
}

void Menu::buttonIsSelected(UIButton* button)
{
    //
    int newIndex = getIndexForButton(button);
    if(newIndex != m_SelectedIndex)
    {
        //
        m_Buttons.at(m_SelectedIndex)->setIsSelected(false);

        //
        m_SelectedIndex = newIndex;
    }
}

void Menu::buttonAction(UIButton* button)
{
    //
}
