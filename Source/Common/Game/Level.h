//
//  Level.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "../Constants/Constants.h"
#include <vector>

#define NUMBER_TEXTURES_COUNT 10

class Tile;
class Player;
class Hero;
class Enemy;
class Tower;
class OpenGLTexture;

class Level
{
public:
	Level(bool isEditingLevel = false);
	~Level();
    
	//Update, paint and reset methods
	void update(double delta);
    void paint();
    void reset();
    
    //save and load levels
    void load(const char* levelName);
    void save(const char* levelName);

	//Input methods
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void keyUpEvent(int keyCode);
	
	// Returns the tile type at the specified index
    TileType getTileTypeForIndex(int index);

	// Returns the tower type at the specified index
	TowerType getTowerTypeForIndex(int index);
    
	//Tile count methods
    unsigned int getNumberOfTiles();
	unsigned int getNumberOfHorizontalTiles();
	unsigned int getNumberOfVerticalTiles();
    
	//Validate that the tile coordinates passed in are valid
	bool validateTileCoordinates(int coordinatesX, int coordinatesY);
    
	//Converts a position in screen space into a position in coordinate space
	int getTileCoordinateForPosition(int position);
    
	//Index methods
	int getTileIndexForPosition(int positionX, int positionY);
	int getTileIndexForCoordinates(int coordinatesX, int coordinatesY);
	int getTileIndexForTile(Tile* tile);
	int getTileIndexForPlayer(Player* player);
	int getSelectedTileIndex();
    
	//Tile methods
	Tile* getTileForPosition(int positionX, int positionY);
	Tile* getTileForCoordinates(int coordinatesX, int coordinatesY);
	Tile* getTileForIndex(int index);
	Tile* getTileForPlayer(Player* player);
    Tile* getTileForChest();
	Tile* getTileForHero();

    //
    void setTileTypeAtPosition(TileType tileType, int positionX, int positionY);
    void setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY);
    void setTileTypeAtIndex(TileType tileType, int index);

	void setTowerTypeAtPosition(TowerType towerType, int positionX, int positionY);
	void setTowerTypeAtCoordinates(TowerType towerType, int coordinatesX, int coordinatesY);
	void setTowerTypeAtIndex(TowerType towerType, int index);
    
    //Coveniance methods to toggle debug paint methods
    void togglePaintTileScoring();
    void togglePaintTileIndexes();

	//Disables the old tiles selection (if ground tile) and
	//enables the newly selected tiles selection (if ground tile)
	void setSelectedTileIndex(int selectedIndex);

	// Getter method for the Hero*
	Hero* getHero();
	Player* getHeroAsPlayer();
    std::vector<Enemy*> getEnemies();
	std::vector<Player*> getEnemiesAsPlayer();

protected:

    // Friend classes so that they can access the protected members
	friend class Player;
	friend class Enemy;
	friend class Hero;
	friend class Tower;
	friend class SlowingTower;
	friend class Game;

	//Protected Member variables
	Hero* m_Hero;
	std::vector<Enemy*> m_Enemies;

	std::vector<Tower*> m_Towers;

	Tile** m_Tiles;
	unsigned int m_HorizontalTiles;
	unsigned int m_VerticalTiles;
	unsigned int m_TileSize;
    unsigned int m_PlayerStartingTileIndex;
	int m_SelectedTileIndex;
    bool m_PaintTileScoring;
    bool m_PaintTileIndexes;

	int m_Difficulty;
	float m_LevelSpeed;
	int m_Currency;
	int m_Score;
	int m_MaxScore;
	int m_Lives;
	int m_Round;
	double m_Timer;
	double m_TimeLimit;

	// True if the game is paused
	bool m_PauseState;

	// The file name of the level
	const char* m_LevelName;

	// Drawing numbers with recursion
	float drawNumber(int number, float x, float y);

	// Textures for the numbers
	OpenGLTexture* m_Numbers[NUMBER_TEXTURES_COUNT];

	// Load the game settings from a JSON file
	void loadSettings();
};

#endif
