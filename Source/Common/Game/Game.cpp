#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "Towers/Tower.h"
#include "Tiles/Tile.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"
#include "../UI/UIButton.h"
#include "../UI/UIToggle.h"


Game::Game()
{
	//Create the level object
	m_Level = new Level();

	// Create the side menu for the towers
	m_TowersMenu = new UISideMenu(this, SideMenuRight);
	m_TowersMenu->addButton(new UIToggle("MenuTileGround"));
	m_TowersMenu->addButton(new UIToggle("MenuTileTree"));
	m_TowersMenu->addButton(new UIToggle("MenuTileWater"));
	m_TowersMenu->addButton(new UIToggle("MenuTileGrass"));

	// Create the side menu for controls, upgrades etc.
	m_ControlMenu = new UISideMenu(this, SideMenuLeft);
	m_ControlMenu->addButton(new UIButton("UpgradeDamageButton"));
	m_ControlMenu->addButton(new UIButton("UpgradeRangeButton"));
	m_ControlMenu->addButton(new UIButton("UpgradeSpeedButton"));

	// Create the label textures
	m_TimeLabel = new OpenGLTexture("Time");
	m_ScoreLabel = new OpenGLTexture("Score");
	m_MoneyLabel = new OpenGLTexture("Money");
	m_LivesLabel = new OpenGLTexture("Lives");

	m_LocationOfSelection = -1;

	m_SelectedTower = NULL;

	m_SelectedTileIndex = -1;

	//Reset everything
	reset();
}

Game::~Game()
{
	// Delete the level object
	if(m_Level != NULL)
	{
		delete m_Level;
		m_Level = NULL;
	}

	// Delete the towers side menu 
	if(m_TowersMenu != NULL)
	{
		delete m_TowersMenu;
		m_TowersMenu = NULL;
	}

	// Delete the controls side mnu
	if(m_ControlMenu != NULL)
	{
		delete m_ControlMenu;
		m_ControlMenu = NULL;
	}

	// delete the label textures

	if(m_TimeLabel != NULL)
	{
		delete m_TimeLabel;
		m_TimeLabel = NULL;
	}

	if(m_ScoreLabel != NULL)
	{
		delete m_ScoreLabel;
		m_ScoreLabel = NULL;
	}

	if(m_MoneyLabel != NULL)
	{
		delete m_MoneyLabel;
		m_MoneyLabel = NULL;
	}
	
	if(m_LivesLabel != NULL)
	{
		delete m_LivesLabel;
		m_LivesLabel = NULL;
	}
}

void Game::update(double delta)
{
	if(m_Level != NULL)
	{
		m_Level->update(delta);
	}

	if(m_TowersMenu != NULL)
	{
		m_TowersMenu->update(delta);
	}

	if(m_ControlMenu != NULL)
	{
		m_ControlMenu->update(delta);
	}
}

void Game::paint()
{
	if(m_Level != NULL)
	{
		m_Level->paint();

		// Paint the tower's range radius if the mouse is hovered over the tower
		for(int i = 0; i < m_Level->m_Towers.size(); i ++)
		{
			if(m_Level->m_Towers.at(i) != NULL)
			{
				if(m_Level->getTileIndexForPosition(m_Level->m_Towers.at(i)->getX(), m_Level->m_Towers.at(i)->getY()) == m_LocationOfSelection)
				{
					m_Level->m_Towers.at(i)->paintTowerRange();
				}
			}
		}
	}

	if(m_TowersMenu != NULL)
	{
		m_TowersMenu->paint();
	}

	if(m_ControlMenu != NULL)
	{
		m_ControlMenu->paint();

		// If the menu is showing and its movement animation is complete
		if(m_ControlMenu->isShowing() && m_ControlMenu->m_FinishedAnimating)
		{
			float x;
			float y;

			// Safety check to make sure texture exists
			if(m_Level->m_Numbers[0] != NULL)
			{
				// Position the time textures to line up with the ControlMenu
				// All number textures are the same size, so just using index 0
				x = m_ControlMenu->m_Width - m_Level->m_Numbers[0]->getSourceWidth();
				y = 0.0f;

				// Draw the game's elapsed time
				y += m_TimeLabel->getTextureHeight() / 2.5f;
				OpenGLRenderer::getInstance()->drawTexture(m_TimeLabel, 5.0f, 0.0f);
				m_Level->drawNumber(m_Level->m_Timer, x, y);

				// Draw the score
				y += m_Level->m_Numbers[0]->getSourceHeight() * 2;
				OpenGLRenderer::getInstance()->drawTexture(m_ScoreLabel, 5.0f, m_TimeLabel->getTextureHeight() / 1.25f);
				m_Level->drawNumber(m_Level->m_Score, x, y + 5.0f);

				// Draw the remaining lives
				y += m_Level->m_Numbers[0]->getSourceHeight() * 2;
				OpenGLRenderer::getInstance()->drawTexture(m_LivesLabel, 5.0f, y);
				m_Level->drawNumber(m_Level->m_Lives, x, y + 15.0f);

				// Draw the player's currency
				y += m_Level->m_Numbers[0]->getSourceHeight() * 2;

				OpenGLRenderer::getInstance()->drawTexture(m_MoneyLabel, 25.0f, y + 5.0f);
				m_Level->drawNumber(m_Level->m_Currency, x - 10.0f, y + 40.0f);
			}
		}
	}

	// Paint the range on the selected tower
	if(m_SelectedTower != NULL)
	{
		m_SelectedTower->paintTowerRange();
	}
}

void Game::reset()
{
	if(m_Level != NULL)
	{
		m_Level->reset();
	}

	m_LocationOfSelection = -1;
	m_SelectedTileIndex = -1;
	m_SelectedTower = NULL;
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

Level* Game::getLevel()
{
	return m_Level;
}

void Game::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	if(m_TowersMenu != NULL)
    {
        m_TowersMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }

	 if(m_ControlMenu != NULL)
    {
        m_ControlMenu->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
    }

	if(m_Level != NULL)
	{
		m_Level->mouseMovementEvent(deltaX, deltaY, positionX, positionY);

		// Updates the current tile being pointed at by the player's cursor
		m_LocationOfSelection = m_Level->getTileIndexForPosition(positionX, positionY);
	}
}

void Game::mouseLeftClickUpEvent(float positionX, float positionY)
{
	// Call the side menus first to prevent accidentally placing towers when trying to clikc on buttons
	if(m_TowersMenu != NULL)
	{
		m_TowersMenu->mouseLeftClickUpEvent(positionX, positionY);
	}

	if(m_ControlMenu != NULL)
	{
		m_ControlMenu->mouseLeftClickUpEvent(positionX, positionY);
	}

	if(m_Level != NULL)
	{
		// Check if a tower object was clicked
		if(m_LocationOfSelection != NULL)
		{
			for(int i = 0; i < m_Level->m_Towers.size(); i++)
			{
				if(m_Level->m_Towers.at(i) != NULL)
				{
					// If a tower is on that tile
					if(m_Level->getTileIndexForPosition(m_Level->m_Towers.at(i)->getX(), m_Level->m_Towers.at(i)->getY()) == m_LocationOfSelection)
					{
						// Set the selected tower
						m_SelectedTower =  m_Level->m_Towers.at(i);
						return;
					}
				}
			}
		}

		// Create towers
		if(m_SelectedTileIndex != -1 )
		{
			if(m_LocationOfSelection != -1)
			{
				TowerType types[] = {TowerTypeTurret, TowerTypeSlowing};
				TowerType type = types[m_SelectedTileIndex];
				int costToBuild = NULL;

				// Calculate how much it costs to place the tower
				switch(type)
				{
				case TowerTypeTurret:
					costToBuild = TOWER_TURRET_COST;
					break;

				case TowerTypeSlowing:
					costToBuild = TOWER_SLOWING_COST;
					break;

				}

				// If the player has enough money to build the tower
				if(costToBuild != NULL && costToBuild <= m_Level->m_Currency)
				{
					// Make sure the tile is walkable - can only build turrets on walkable tiles
					if(m_Level->getTileForIndex(m_LocationOfSelection) != NULL)
					{
						if(!m_Level->getTileForIndex(m_LocationOfSelection)->isWalkableTile())
						{
							return;
						}
					}

					// Make a temporary player vector 
					std::vector<Player*> enemies = m_Level->getEnemiesAsPlayer();
					bool tileIsOccupied = false;

					// Cycle through enemies to see if any occupy the tile
					for(int i = 0; i < enemies.size(); i++)
					{
						if(m_Level->getTileIndexForPlayer(enemies.at(i)) == m_LocationOfSelection)
						{
							tileIsOccupied = true;
						}
					}

					// Check if the hero occupies the tile
					if(m_Level->getTileIndexForPlayer(m_Level->getHeroAsPlayer()) == m_LocationOfSelection)
					{
						tileIsOccupied = true;
					}
					
					// Check if it's the chest tile
					if(m_Level->getTileIndexForTile(m_Level->getTileForChest()) == m_LocationOfSelection)
					{
						tileIsOccupied = true;
					}

					// If the tile is not occupied
					if(!tileIsOccupied)
					{
						// Create the tower at the location
						m_Level->setTowerTypeAtIndex(type, m_LocationOfSelection);

						// Deduct the cost from the player's currency
						m_Level->m_Currency -= costToBuild;

						return;
					}
				}
			}
		}

		m_Level->mouseLeftClickUpEvent(positionX, positionY);
	}
}

void Game::keyUpEvent(int keyCode)
{
	// Go back to the main menu if the escape key is pressed
	if(keyCode == KEYCODE_ESCAPE)
	{
		if(ScreenManager::getInstance()->getCurrentScreen()->getName() == GAME_SCREEN_NAME)
		{
			// Go to the main menu
			ScreenManager::getInstance()->switchScreen(MAIN_MENU_SCREEN_NAME);
		}
		else
		{
			m_SelectedTower = NULL;

			// Reset the level (only called from other menus)
			m_Level->load(m_Level->m_LevelName);

			// Reset the side menus
			if(m_TowersMenu != NULL && m_ControlMenu != NULL)
			{
				if(m_TowersMenu->isShowing() || m_ControlMenu->isShowing())
				{
					keyUpEvent(KEYCODE_TAB);
				}

				// Reset the selected index for the tower menu, so when the game is reset 
				// the player wont accidentally create the last selected tower
				UIToggle* previousToggle = (UIToggle*)m_TowersMenu->getButtonForIndex(m_SelectedTileIndex);

				if(previousToggle != NULL)
				{
					previousToggle->setIsToggled(false);
				}

				m_SelectedTileIndex = -1;
			}
		}
	}
	else if(keyCode == KEYCODE_TAB)
	{
		// Display/hide the towers side menu
		if(m_TowersMenu != NULL)
		{
			m_TowersMenu->isShowing() == true ? m_TowersMenu->hide() : m_TowersMenu->show();
		}

		// Display/hide the controls side menu
		if(m_ControlMenu != NULL)
		{
			m_ControlMenu->isShowing() == true ? m_ControlMenu->hide() : m_ControlMenu->show();
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

void Game::sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex)
{
	if(sideMenu == m_ControlMenu)
	{
		if(m_Level != NULL)
		{
			switch(buttonIndex)
			{
			case 0:
				// Upgrade tower damage
				if(m_SelectedTower != NULL)
				{
					if(m_SelectedTower->m_NumberOfUpgrades < TOWER_MAX_UPGRADES)
					{
						if(TOWER_UPGRADE_COST <= m_Level->m_Currency)
						{
							m_Level->m_Currency -= TOWER_UPGRADE_COST;
							// Gain 25% more damage each upgrade
							m_SelectedTower->m_Power *= 1.25;
							m_SelectedTower->m_NumberOfUpgrades++;
							m_LocationOfSelection = -1;
						}
					}
				}
				break;

			case 1:
				// Upgrade tower range
				if(m_SelectedTower != NULL)
				{
					if(m_SelectedTower->m_NumberOfUpgrades < TOWER_MAX_UPGRADES)
					{
						if(TOWER_UPGRADE_COST <= m_Level->m_Currency)
						{
							m_Level->m_Currency -= TOWER_UPGRADE_COST;
							// Gain 15% more range each upgrade
							m_SelectedTower->m_Range *= 1.15;
							m_SelectedTower->m_NumberOfUpgrades++;
							m_LocationOfSelection = -1;
						}
					}
				}
				break;

			case 2:
				// Upgrade tower fire speed
				if(m_SelectedTower != NULL)
				{
					if(m_SelectedTower->m_NumberOfUpgrades < TOWER_MAX_UPGRADES)
					{
						if(TOWER_UPGRADE_COST <= m_Level->m_Currency)
						{
							m_Level->m_Currency -= TOWER_UPGRADE_COST;
							// Fire 15% faster with each upgrade
							m_SelectedTower->m_Speed /= 1.15;
							m_SelectedTower->m_NumberOfUpgrades++;
							m_LocationOfSelection = -1;
						}
					}
				}
				break;
			}
		}
	}
}

void Game::sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex)
{
	if(sideMenu == m_TowersMenu)
    {
		UIToggle* previousToggle = (UIToggle*)m_TowersMenu->getButtonForIndex(m_SelectedTileIndex);

		if(previousToggle != NULL)
        {
            previousToggle->setIsToggled(false);
        }
    
        //Set the selected tile index
        m_SelectedTileIndex = toggle->isToggled() == true ? toggleIndex : -1;
        
        //Hide the options and tiles menus
        m_TowersMenu->hide();
		m_ControlMenu->hide();

		m_LocationOfSelection = -1;
	}
}