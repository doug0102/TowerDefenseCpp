//
//  Level.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Level.h"
#include "Player.h"
#include "Hero.h"
#include "Enemy.h"
#include "PathFinder.h"

#include "Tiles/Tile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/TreeTile.h"
#include "Tiles/WaterTile.h"
#include "Tiles/GrassTile.h"
#include "Tiles/BrickTile.h"
#include "Tiles/ChestTile.h"

#include "Towers/Tower.h"
#include "Towers/TurretTower.h"
#include "Towers/SlowingTower.h"

#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include"../Utils/Utils.h"
#include "../Libraries/jsoncpp/json.h"
#include <stdlib.h>
#include <fstream>

#include"../Utils/Logger/Logger.h"


Level::Level(bool isEditingLevel) :
    m_HorizontalTiles(0),
    m_VerticalTiles(0),
    m_TileSize(EMPTY_LEVEL_TILE_SIZE),
    m_PlayerStartingTileIndex(EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX),
    m_Hero(NULL),
    m_Tiles(NULL),
	m_Towers(NULL),
    m_SelectedTileIndex(-1),
    m_PaintTileScoring(false),
    m_PaintTileIndexes(false),
	m_LevelName(NULL),
	m_Timer(0.0),
	m_TimeLimit(0.0),
	m_Difficulty(0)
{
    //Create the hero object
    if(isEditingLevel == false)
    {
        m_Hero = new Hero(this);

		float minSpeed = PLAYER_MIN_SPEED;
		float maxSpeed = PLAYER_SPEED * 0.50f;	// Max speed is 25% slower than the hero
		GDRandom random;
		random.randomizeSeed();

		// Create enemy objects
		for(int i = 0; i < ENEMY_COUNT; i++)
		{
			float speed = minSpeed + random.random(maxSpeed - minSpeed);
			Enemy* enemy = new Enemy(this, speed);
			m_Enemies.push_back(enemy);
		}
    }
    
    //Calculate the number of horizontal and vertical tiles
    m_HorizontalTiles = ScreenManager::getInstance()->getScreenWidth() / m_TileSize;
    m_VerticalTiles = ScreenManager::getInstance()->getScreenHeight() / m_TileSize;
    
    //Allocate the tiles array, the inheriting class will populate this array with Tile objects
	m_Tiles = new Tile*[m_HorizontalTiles * m_VerticalTiles];
    
    //Initialize all the tiles to NULL
    for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
    {
        m_Tiles[i] = NULL;
    }

	// Create a texture for each number, it will match the index in the array
	for(int i = 0; i < NUMBER_TEXTURES_COUNT; i++)
	{
		std::string path = "Numbers";
		char buffer[2];
		path.append(itoa(i, buffer, 10));

		m_Numbers[i] = new OpenGLTexture(path.c_str());
	}
    
	// Set the level's speed to the default value
	m_LevelSpeed = GAME_DEFAULT_SPEED;

	// Set the level's starting currency (gold to spend on towers)
	m_Currency = GAME_STARTING_CURRENCY;

	m_Score = 0;

	// Set the level's maximum score to the default value
	m_MaxScore = GAME_MAX_SCORE_DEFAULT;

	m_Lives = GAME_STARTING_LIVES;

	m_Round = 1;

	m_TimeLimit = GAME_TIME_LIMIT_DEFAULT;

    //Load an empty level
    load(NULL);

	m_LevelName = NULL;

	m_PauseState = false;
}

Level::~Level()
{
    //Delete the hero object
	if(m_Hero != NULL)
	{
		delete m_Hero;
		m_Hero = NULL;
	}

	for(int i = 0; i < m_Enemies.size(); i++)
	{
		delete m_Enemies.at(i);
		m_Enemies.at(i) = NULL;
	}

	m_Enemies.clear();
    
    //Delete the tiles array, the inheriting class
    //must delete the object in this array itself
	if(m_Tiles != NULL)
	{
        //Cycle through and delete all the tile objects in the array
        for(int i = 0; i < getNumberOfTiles(); i++)
        {
            if(m_Tiles[i] != NULL)
            {
                delete m_Tiles[i];
                m_Tiles[i] = NULL;
            }
        }
        
		delete[] m_Tiles;
		m_Tiles = NULL;
	}

	// Delete the number textures
	for(int i = 0; i < NUMBER_TEXTURES_COUNT; i++)
	{
		if(m_Numbers[i] != NULL)
		{
			delete m_Numbers[i];
			m_Numbers[i] = NULL;
		}
	}

	// Delete the towers
	for(int i = 0; i < m_Towers.size(); i++)
	{
		if(m_Towers.at(i) != NULL)
		{
			delete m_Towers[i];
			m_Towers[i] = NULL;
		}
	}

	m_Towers.clear();
}

void Level::update(double aDelta)
{
	// Only update when the game isn't paused
	if(!m_PauseState)
	{
		// Increment the timer
		m_Timer += aDelta;

		//Update all the game tiles
		for(int i = 0; i < getNumberOfTiles(); i++)
		{
			if(m_Tiles[i] != NULL)
			{
				m_Tiles[i]->update(aDelta);
			}
		}

		//Update the Hero
		if(m_Hero != NULL)
		{
			if(m_Hero->getIsActive())
			{
				m_Hero->update(aDelta);
			}
		}

		// Update the towers
		for(int i = 0; i < m_Towers.size(); i++)
		{
			if(m_Towers.at(i) != NULL)
			{
				m_Towers.at(i)->update(aDelta);
			}
		}

		// Holds the number of active enemies (alive)
		int numberOfActiveEnemies = 0;

		// Update the enemies
		for(int i = 0; i < m_Enemies.size(); i++)
		{
			// Only update the active enemies
			if(m_Enemies.at(i)->getIsActive() == true)
			{
				m_Enemies.at(i)->update(aDelta);

				// Increment the active enemies counter
				numberOfActiveEnemies++;
			}
		}

		// Reset the enemies once they're all dead
		if(numberOfActiveEnemies <= 0)
		{
			std::vector<Tile*> spawnableLocations;

			for(int i = 0; i < getNumberOfTiles(); i++)
			{
				// Brick tiles are spawnable tiles
				if(m_Tiles[i]->getType() == TILE_BRICK_TYPE)
				{
					spawnableLocations.push_back(m_Tiles[i]);
				}
			}


			for(int i = 0; i < m_Enemies.size(); i++)
			{
				m_Enemies.at(i)->setCurrentTile(spawnableLocations[i]);
				m_Enemies.at(i)->reset();
			}

			// Increase the round
			m_Round++;
		}

		// If the game score or game time is greater or equal to the max score
		if(m_Score >= m_MaxScore || m_Timer >= m_TimeLimit)
		{
			// Only proceeds if the current screen is the game screen, NOT the level editor
			Screen* currentScreen = ScreenManager::getInstance()->getCurrentScreen();
			if(currentScreen == ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))
			{
				// Display the level complete screen
				ScreenManager::getInstance()->switchScreen(LEVEL_COMPLETE_SCREEN_NAME);
			}
		}

		// If there are no lives remaining or the hero is dead, the game is over
		if(m_Hero != NULL)
		{
			if(m_Lives <= 0 || !m_Hero->getIsActive())
			{
				// Only proceeds if the current screen is the game screen, NOT the level editor
				Screen* currentScreen = ScreenManager::getInstance()->getCurrentScreen();
				if(currentScreen == ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME))
				{
					// Display the game over screen
					ScreenManager::getInstance()->switchScreen(GAME_OVER_SCREEN_NAME);

					Screen* s = ScreenManager::getInstance()->getScreenForName(GAME_OVER_SCREEN_NAME);

				}
			}
		}
	}
}

void Level::paint()
{
	//Cycle through and paint all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
        //Safety check the tile
		if(m_Tiles[i] != NULL)
		{
            //Paint the tile
            m_Tiles[i]->paint();
            
            //If the paint tile indexes flag is set to true,
            //draw the index number on the tiles
            if(m_PaintTileIndexes == true)
            {
                m_Tiles[i]->paintIndex(i);
            }
		}
	}
    
	//Paint the Player
	if(m_Hero != NULL)
	{
        //If paint tile scoring flag is set to true,
        //draw the path scoring
        if(m_PaintTileScoring == true)
        {
			// Paint the tile scores
			m_Hero->getPathFinder()->paint();
        }
        
		// Only paint if the player is active
		if(m_Hero->getIsActive())
		{
			//Paint the player
			m_Hero->paint();
		}
	}

	// Paint the enemies
	for(int i = 0; i < m_Enemies.size(); i++)
	{
		// Only paint the active enemies
		if(m_Enemies.at(i)->getIsActive() == true)
		{
			m_Enemies.at(i)->paint();
		}
	}

	// Paint the towers
	for(int i = 0; i < m_Towers.size(); i++)
	{
		if(m_Towers.at(i) != NULL)
		{
			m_Towers.at(i)->paint();
		}
	}
}

void Level::reset()
{
	// Load the settings
	loadSettings();

	// Delete the towers
	for(int i = 0; i < m_Towers.size(); i++)
	{
		if(m_Towers.at(i) != NULL)
		{
			// Reset any tiles that had towers on them
			Tile* t = getTileForIndex(getTileIndexForPosition(m_Towers.at(i)->getX(), m_Towers.at(i)->getY()));
			if(t->getX() == m_Towers.at(i)->getX() && t->getY() == m_Towers.at(i)->getY())
			{
				t->setHasTower(false);
			}

			delete m_Towers.at(i);
			m_Towers.at(i) = NULL;
		}
	}

	//Cycle through and reset all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->reset();
		}
	}

	m_Score = 0;

	m_Timer = 0;

	m_Round = 1;

	m_Lives = GAME_STARTING_LIVES;

	m_Currency = GAME_STARTING_CURRENCY;

	m_PauseState = false;

	// Make a temporary player vector that holds both hero and enemy objects
	std::vector<Player*> players;

	// Add the hero to the vector
	if(m_Hero != NULL)
	{
		players.push_back(m_Hero);
	}

	// Add the enemies
	for(int i = 0; i < m_Enemies.size(); i++)
	{
		players.push_back(m_Enemies.at(i));
	}

	// Random number generator for the spawn indexes
	GDRandom random;
	random.randomizeSeed();
	int tileIndex = -1;
	std::vector<int> usedTileIndexes;


	// Cycle through the player objects
	for(int i = 0; i < players.size(); i++)
	{
		// Set tile index to -1
		tileIndex = -1;

		while(tileIndex == -1)
		{
			tileIndex = random.random(getNumberOfTiles());
			
			// Safety check
			if(getTileForIndex(tileIndex)->isWalkableTile() == false)
			{
				tileIndex = -1;
			}
			else
			{
				// Cycle through and make sure the tile hasnt been used already
				for(int j = 0; j < usedTileIndexes.size(); j++)
				{
					if(usedTileIndexes.at(j) == tileIndex)
					{
						tileIndex = -1;
						break;
					}
				}

				// Safety check that tile index isnt -1
				if(tileIndex != -1)
				{
					players.at(i)->setCurrentTile(getTileForIndex(tileIndex));
					players.at(i)->reset();
					usedTileIndexes.push_back(tileIndex);
				}
			}
		}
	}
}

void Level::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	if(m_Hero != NULL)
	{
		m_Hero->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}
}

void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
	if(m_Hero != NULL)
	{
		m_Hero->mouseLeftClickUpEvent(aPositionX, aPositionY);
	}
}

void Level::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_R)
    {
        reset();
    }
    else if(keyCode == KEYCODE_S)
    {
        togglePaintTileScoring();
    }
    else if(keyCode == KEYCODE_I)
    {
        togglePaintTileIndexes();
    }
	else
    {
        if(m_Hero != NULL)
		{
			m_Hero->keyUpEvent(keyCode);
		}
    }
}

void Level::load(const char* levelName)
{
    //If the level name isn't NULL load the level from the filesystem,
    //if it is NULL load an empty level with just ground tiles
    if(levelName != NULL)
    {
        //load the level from file

		std::ifstream inputStream;

		//open the file
		inputStream.open(levelName, std::ifstream::in | std::ifstream::binary);

		// if the file exists
		if(inputStream.is_open() == true)
		{
			// Find out how many bytes are in the file
			inputStream.seekg(0, inputStream.end);
			long long bufferSize = inputStream.tellg();

			// Seek back to the start of the file for reading
			inputStream.seekg(0, inputStream.beg);

			// Create a buffer for the data
			char* buffer = new char[bufferSize];

			// Read the data from the stream into the buffer
			inputStream.read(buffer, (int)bufferSize);

			//close the input stream
			inputStream.close();

			//Tile variables
			int tileIndex = 0;
			float tileX = 0.0f;
			float tileY = 0.0f;

			//Cycle through all the tiles and create them
			for(int v = 0; v < getNumberOfVerticalTiles(); v++)
			{
				for(int h = 0; h < getNumberOfHorizontalTiles(); h++)
				{
					switch(buffer[tileIndex])
					{
					case TileTypeGround:
						setTileTypeAtIndex(TileTypeGround, tileIndex);
						break;
					case TileTypeTree:
						setTileTypeAtIndex(TileTypeTree, tileIndex);
						break;
					case TileTypeWater:
						setTileTypeAtIndex(TileTypeWater, tileIndex);
						break;
					case TileTypeGrass:
						setTileTypeAtIndex(TileTypeGrass, tileIndex);
						break;
					case TileTypeBrick:
						setTileTypeAtIndex(TileTypeBrick, tileIndex);
						break;
					case TileTypeChest:
						setTileTypeAtIndex(TileTypeChest, tileIndex);
						break;
					}


					m_Tiles[tileIndex]->setPosition(tileX, tileY);
					m_Tiles[tileIndex]->setSize(m_TileSize, m_TileSize);

					//Increment the tile index
					tileIndex++;

					//And increment the tile x position
					tileX += m_TileSize;
				}

				//Increment the tile y position and reset the tile x position, since we started a new row
				tileY += m_TileSize;
				tileX = 0.0f;
			}

			delete buffer;
			buffer = NULL;

			m_LevelName = levelName;
		}
    }
    else
    {
		for(int i = 0; i < getNumberOfTiles(); i++)
		{
			setTileTypeAtIndex(TileTypeGround, i);
		}
    }
    
    //The level is loaded, reset everything
    reset();
}

void Level::save(const char* levelName)
{
	// only save a level if the file name isn't null
	if(levelName != NULL)
	{
		//Buffer size is the number of tiles

		// The thing to save
		char* buffer = new char[getNumberOfTiles()];

		for(int i = 0; i < getNumberOfTiles(); i++)
		{
			buffer[i] = char(m_Tiles[i]->getTileType());
		}

		std::ofstream outputStream;

		//Open the file
		outputStream.open(levelName, std::ofstream::out | std::ofstream::binary);

		 //Did the file open?
		if(outputStream.is_open() == true)
		{

			//Write the buffer
			outputStream.write((char*)buffer, getNumberOfTiles());
        
			//Make sure to close the file stream
			outputStream.close();

			// delete the buffer
			delete buffer;
			buffer = NULL;
		}
		else
		{
			//This may be a place where you could throw an exception in your game,
			//if you are opening a file for reading OR writing and it doesn't open.

		}
	}

}

TileType Level::getTileTypeForIndex(int index)
{
    if(index >= 0 && index < getNumberOfTiles())
    {
        return m_Tiles[index]->getTileType();
    }
    return TileTypeUnknown;
}

TowerType Level::getTowerTypeForIndex(int index)
{
	if(index >= 0 && index < getNumberOfTiles())
	{
		if(m_Tiles[index]->getTower() != NULL)
		{
			return m_Tiles[index]->getTower()->getTowerType();
		}
	}
	return TowerTypeUnknown;
}

unsigned int Level::getNumberOfTiles()
{
    return getNumberOfHorizontalTiles() * getNumberOfVerticalTiles();
}

unsigned int Level::getNumberOfHorizontalTiles()
{
	return m_HorizontalTiles;
}

unsigned int Level::getNumberOfVerticalTiles()
{
	return m_VerticalTiles;
}

bool Level::validateTileCoordinates(int aCoordinatesX, int aCoordinatesY)
{
    if(aCoordinatesX < 0 || aCoordinatesY < 0 || aCoordinatesX >= getNumberOfHorizontalTiles() || aCoordinatesY >= getNumberOfVerticalTiles())
	{
        return false;
    }
    return true;
}

int Level::getTileCoordinateForPosition(int aPosition)
{
	return (aPosition / m_TileSize);
}

int Level::getTileIndexForPosition(int aPositionX, int aPositionY)
{
	int coordinatesX = getTileCoordinateForPosition(aPositionX);
	int coordinatesY = getTileCoordinateForPosition(aPositionY);
	return getTileIndexForCoordinates(coordinatesX, coordinatesY);
}

int Level::getTileIndexForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	//Validate the coordinates, then calculate the array index
	if(validateTileCoordinates(aCoordinatesX, aCoordinatesY) == true)
	{
		return aCoordinatesX + (aCoordinatesY * getNumberOfHorizontalTiles());
	}
    
	return -1;
}

int Level::getTileIndexForTile(Tile* aTile)
{
	return getTileIndexForPosition(aTile->getX(), aTile->getY());
}

int Level::getTileIndexForPlayer(Player* player)
{
	return getTileIndexForPosition(player->getX(), player->getY());
}

Tile* Level::getTileForPosition(int aPositionX, int aPositionY)
{
	return getTileForIndex(getTileIndexForPosition(aPositionX, aPositionY));
}

Tile* Level::getTileForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	return getTileForIndex(getTileIndexForCoordinates(aCoordinatesX, aCoordinatesY));
}

Tile* Level::getTileForIndex(int aIndex)
{
    //Safety check the index bounds
	if(aIndex >= 0 && aIndex < getNumberOfTiles())
	{
		return m_Tiles[aIndex];
	}
    
    //If we got here, it means the index passed in was out of bounds
	return NULL;
}

Tile* Level::getTileForPlayer(Player* player)
{
	return getTileForPosition(player->getX(), player->getY());
}

Tile* Level::getTileForChest()
{
	for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
    {
		if(m_Tiles[i] != NULL)
		{
			if(m_Tiles[i]->getType() == TILE_CHEST_TYPE)
			{
				return m_Tiles[i];
			}
		}
    } 
	return NULL;
}

Tile* Level::getTileForHero()
{
	return m_Hero->m_CurrentTile;
}

void Level::setTileTypeAtPosition(TileType tileType, int positionX, int positionY)
{
    setTileTypeAtIndex(tileType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY)
{
    setTileTypeAtIndex(tileType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTileTypeAtIndex(TileType tileType, int index)
{
    //Safety check the index
    if(index >= 0 && index < getNumberOfTiles())
	{
        //Don't replace the tile if its the same type of tile that already exists
        if(m_Tiles[index] != NULL && m_Tiles[index]->getTileType() == tileType)
        {
            return;
        }
    
        //Delete the tile at the index, if one exists
        if(m_Tiles[index] != NULL)
        {
            delete m_Tiles[index];
            m_Tiles[index] = NULL;
        }
        
        //Create the new tile based on the TileType
        switch (tileType)
        {
            case TileTypeGround:
                m_Tiles[index] = new GroundTile();
                break;

			case TileTypeTree:
                m_Tiles[index] = new TreeTile();
                break;

			case TileTypeWater:
                m_Tiles[index] = new WaterTile();
                break;

			case TileTypeGrass:
				m_Tiles[index] = new GrassTile();
				break;

			case TileTypeBrick:
				m_Tiles[index] = new BrickTile();
				break;

			case TileTypeChest:
				m_Tiles[index] = new ChestTile();
				break;

            case TileTypeUnknown:
            default:
                m_Tiles[index] = NULL;
                break;
        }
        
        //Calculate the coordinates and set the tile position and size
        int coordinateX = (index % getNumberOfHorizontalTiles());
        int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
        m_Tiles[index]->setPosition(coordinateX  * m_TileSize, coordinateY * m_TileSize);
        m_Tiles[index]->setSize(m_TileSize, m_TileSize);
	}
}

void Level::setTowerTypeAtPosition(TowerType towerType, int positionX, int positionY)
{
	setTowerTypeAtIndex(towerType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTowerTypeAtCoordinates(TowerType towerType, int coordinatesX, int coordinatesY)
{
	setTowerTypeAtIndex(towerType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTowerTypeAtIndex(TowerType towerType, int index)
{
	if(index >= 0 && index < getNumberOfTiles())
	{
		switch (towerType)
        {
		case TowerTypeTurret:
			m_Towers.push_back(new TurretTower(this));
			m_Towers.back()->setPosition(m_Tiles[index]->getX(), m_Tiles[index]->getY());
			break;
			
		case TowerTypeSlowing:
			m_Towers.push_back(new SlowingTower(this));
			m_Towers.back()->setPosition(m_Tiles[index]->getX(), m_Tiles[index]->getY());
			break;
		}



		/*


		// Don't replace the tower if a tower of the same type already exists there
		if(m_Tiles[index] != NULL && m_Tiles[index]->getTower() != NULL)
		{
			if(m_Tiles[index]->getTower()->getTowerType() == towerType)
			{
				return;
			}
		}

		// Delete the tower at the index, if the one exists already
		if(m_Tiles[index] != NULL)
		{
			if(m_Tiles[index]->getTower() != NULL)
			{
				m_Tiles[index]->setTower(NULL);
			}

			// Create a new tower object based on the TowerType
			switch(towerType)
			{
			case TowerTypeTurret:
				m_Tiles[index]->setTower(new TurretTower(this));
				break;

				//TODO: Make sure to add future towers here for object creation

			case TowerTypeUnknown:
			default:
				
				break;
			}

			// Set the towers position and size
			if(m_Tiles[index]->getTower() != NULL)
			{
				int coordinateX = (index % getNumberOfHorizontalTiles());
				int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());

				Tower* tower = m_Tiles[index]->getTower();
				float x = (coordinateX * m_TileSize) + (m_TileSize - tower->getWidth()) / 2.0f;
				float y = (coordinateY * m_TileSize) + (m_TileSize - tower->getHeight()) / 2.0f;
				tower->setPosition(x, y);
			}
		}

		*/
	}
}

void Level::togglePaintTileScoring()
{
    m_PaintTileScoring = !m_PaintTileScoring;
}

void Level::togglePaintTileIndexes()
{
    m_PaintTileIndexes = !m_PaintTileIndexes;
}

void Level::setSelectedTileIndex(int aSelectedIndex)
{
	//Deselect the previously selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(false);
	}
    
	//Set the new tile index
	m_SelectedTileIndex = aSelectedIndex;
    
	//Selected the newly selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(true);
	}
}

int Level::getSelectedTileIndex()
{
	return m_SelectedTileIndex;
}

Hero* Level::getHero()
{
	return m_Hero;
}

Player* Level::getHeroAsPlayer()
{
	Player* hero = m_Hero;
	return hero;
}

std::vector<Enemy*> Level::getEnemies()
{
	return m_Enemies;
}

std::vector<Player*> Level::getEnemiesAsPlayer()
{
	std::vector<Player*> enemies;

	for(int i = 0; i < m_Enemies.size(); i++)
	{
		enemies.push_back(m_Enemies.at(i));
	}

	return enemies;
}

float Level::drawNumber(int number, float x, float y)
{
	// Isolate the last  digit in the number
	int digitToDraw = number % 10;
	OpenGLTexture* digit = m_Numbers[digitToDraw];

	// Get the width of the digit to draw, subtract width from x
	float width = digit->getSourceWidth();
	x -= width;

	// Draw the number texture
	OpenGLRenderer::getInstance()->drawTexture(digit, x, y);

	// If the number is greater or equal to 10 we have more digits to draw
	if(number >= 10)
	{
		width += drawNumber(number / 10, x, y);
	}

	return width;
}

void Level::loadSettings()
{
	std::ifstream inputStream;
	inputStream.open("settings", std::ifstream::in);

	// Parse the json file
	Json::Value root;
	Json::Reader reader;

	// Did the file parse successfully?
	if(reader.parse(inputStream, root, false))
	{
		m_Difficulty = root["Difficulty"].asInt();
		m_MaxScore = root["ScoreLimit"].asInt();
		m_TimeLimit = root["TimeLimit"].asDouble();
	}

	inputStream.close();
}