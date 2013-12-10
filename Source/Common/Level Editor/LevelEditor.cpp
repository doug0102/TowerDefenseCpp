//
//  LevelEditor.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-25.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "LevelEditor.h"
#include "../Constants/Constants.h"
#include "../Game/Level.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"
//#include "LoadingMenu.h"
#include "../Menus/LoadingMenu.h"

LevelEditor::LevelEditor() :
    m_TilesMenu(NULL),
    m_Level(NULL),
    m_IsMouseDown(false),
    m_SelectedTileIndex(-1)
{
    //Create the Tiles menu items
    m_TilesMenu = new UISideMenu(this, SideMenuRight);
    m_TilesMenu->addButton(new UIToggle("MenuTileGround"));
	m_TilesMenu->addButton(new UIToggle("MenuTileTree"));
	m_TilesMenu->addButton(new UIToggle("MenuTileWater"));
	m_TilesMenu->addButton(new UIToggle("MenuTileGrass"));
	m_TilesMenu->addButton(new UIToggle("MenuTileBrick"));
	m_TilesMenu->addButton(new UIToggle("MenuTileChest"));

	// Create the controls side menu
	m_ControlMenu = new UISideMenu(this, SideMenuLeft);
	m_ControlMenu->addButton(new UIButton("ButtonClear"));
	m_ControlMenu->addButton(new UIButton("ButtonLoad"));
	m_ControlMenu->addButton(new UIButton("ButtonSave"));
	m_ControlMenu->addButton(new UIButton("ButtonExit"));
    
    //Create the level object
    m_Level = new Level(true);
    
    //Reset everything
    reset();
}

LevelEditor::~LevelEditor()
{
    if(m_Level != NULL)
    {
        delete m_Level;
        m_Level = NULL;
    }
    
    if(m_TilesMenu != NULL)
    {
        delete m_TilesMenu;
        m_TilesMenu = NULL;
    }

	 if(m_ControlMenu != NULL)
    {
        delete m_ControlMenu;
        m_ControlMenu = NULL;
    }
}

const char* LevelEditor::getName()
{
    return LEVEL_EDITOR_SCREEN_NAME;
}

void LevelEditor::update(double delta)
{
    if(m_Level != NULL)
    {
        m_Level->update(delta);
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->update(delta);
    }

	 if(m_ControlMenu != NULL)
    {
        m_ControlMenu->update(delta);
    }
}

void LevelEditor::paint()
{
    if(m_Level != NULL)
    {
        m_Level->paint();
    }

    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->paint();
    }

	if(m_ControlMenu != NULL)
    {
        m_ControlMenu->paint();
    }
}

void LevelEditor::reset()
{
    if(m_Level != NULL)
    {
        m_Level->reset();
    }
}

void LevelEditor::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{    
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }

	 if(m_ControlMenu != NULL)
    {
        m_ControlMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }
    
    if(m_Level != NULL)
    {        
        if(m_SelectedTileIndex != -1 && m_IsMouseDown == true)
        {
			TileType types[] = {TileTypeGround, TileTypeTree, TileTypeWater, TileTypeGrass, TileTypeBrick, TileTypeChest};
			TileType type = types[m_SelectedTileIndex];

            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
}

void LevelEditor::mouseLeftClickDownEvent(float positionX, float positionY)
{
    //Set the mouse down flag
    m_IsMouseDown = true;
}

void LevelEditor::mouseLeftClickUpEvent(float positionX, float positionY)
{
    //Set the mouse up flag
    m_IsMouseDown = false;
    
    //Safety check the level pointer, then set the new tile type in the index
    if(m_Level != NULL)
    {
        if(m_SelectedTileIndex != -1 && m_TilesMenu->isShowing() == false)
        {
			TileType types[] = {TileTypeGround, TileTypeTree, TileTypeWater, TileTypeGrass, TileTypeBrick, TileTypeChest};
			TileType type = types[m_SelectedTileIndex];

            m_Level->setTileTypeAtPosition(type, positionX, positionY);
        }
    }
    
    //Notify the tiles menu of the mouse event
    if(m_TilesMenu != NULL)
    {
        m_TilesMenu->mouseLeftClickUpEvent(positionX, positionY);
    }

	//Notify the control menu of the mouse event
    if(m_ControlMenu != NULL)
    {
        m_ControlMenu->mouseLeftClickUpEvent(positionX, positionY);
    }
}

void LevelEditor::keyUpEvent(int keyCode)
{
	// Keyup events
    if(keyCode == KEYCODE_TAB)
    {
		// Display/hide the tile side menu
        if(m_TilesMenu != NULL)
        {
            m_TilesMenu->isShowing() == true ? m_TilesMenu->hide() : m_TilesMenu->show();
        }

		// Display/hide the control side menu
		if(m_ControlMenu != NULL)
        {
            m_ControlMenu->isShowing() == true ? m_ControlMenu->hide() :m_ControlMenu->show();
        }
    }
	else if(keyCode == KEYCODE_T)
	{
		if(m_Level != NULL)
		{
			//m_Level->setTowerTypeAtIndex(TowerTypeTurret, 100);

		}
	}
	else if(keyCode == KEYCODE_Y)
	{
		if(m_Level != NULL)
		{
			//m_Level->removeTowerAtIndex(100);
		}
	}
	else if(keyCode == KEYCODE_P)
	{
		// If the current screen is the load screen, load the level.
		if(ScreenManager::getInstance()->getCurrentScreen() == ScreenManager::getInstance()->getScreenForName(LOAD_MENU_SCREEN_NAME))
		{
			// This file is the level selected from the load menu screen
			m_Level->load("TempLoad.txt");
		}
	}
    else
    {
        if(m_Level != NULL)
        {
            m_Level->keyUpEvent(keyCode);
        }
    }
}

void LevelEditor::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
	if(sideMenu == m_ControlMenu)
	{
		switch(buttonIndex)
		{
		case 0:
			// clear the level
			m_Level->load(NULL);
			break;
		case 1:
			// Switch to the load menu screen
			ScreenManager::getInstance()->switchScreen(LOAD_MENU_SCREEN_NAME);
			break;
		case 2:
			// Make a temporary save of the level
			m_Level->save("TempSave.txt");
			
			// Switch to the save menu screen
			ScreenManager::getInstance()->switchScreen(SAVE_MENU_SCREEN_NAME);
			break;
		case 3:
			// go back to main menu
			ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
			break;
		}

		 m_TilesMenu->hide();
		 m_ControlMenu->hide();
	}
}

void LevelEditor::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
    if(sideMenu == m_TilesMenu)
    {
        //Un-toggled the previously selected toggle
        UIToggle* previousToggle = (UIToggle*)m_TilesMenu->getButtonForIndex(m_SelectedTileIndex);
        if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        }
    
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_TilesMenu->hide();
		m_ControlMenu->hide();
    }
}
