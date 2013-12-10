//
//  Tile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Tile.h"
#include "../Towers/Tower.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Utils/Utils.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <math.h> 


Tile::Tile(TileType tileType, const char* tileTexture, bool aIsWalkableTile)
{
    //Initialize the walkable tile, selected and path flags
    m_TileType = tileType;
    m_IsWalkableTile = aIsWalkableTile;
    m_IsSelected = false;
    m_IsPath = false;
	m_Damaged = false;
	m_Tower = NULL;

	m_DamagedTexture = new OpenGLTexture("TerrainDamage");

    //Create the tile texture
    if(tileTexture != NULL)
    {
        m_Texture = OpenGLTextureCache::getInstance()->getTexture(tileTexture);
    }
    
    //Create the selected tile object
    m_SelectedTile = OpenGLTextureCache::getInstance()->getTexture(RES_SELECTED_TILE);
    
    //Create the tile index number OpenGLTextures
    m_TileIndexNumbers = new OpenGLTexture*[RES_TILE_INDEX_NUMBERS_COUNT];
    for(int i = 0; i < RES_TILE_INDEX_NUMBERS_COUNT; i++)
    {
        m_TileIndexNumbers[i] = OpenGLTextureCache::getInstance()->getTexture(RES_TILE_INDEX_NUMBERS[i]);
    }
    
    //Create the tile scoring number OpenGLTextures
    m_TileScoreNumbers = new OpenGLTexture*[RES_TILE_SCORE_NUMBERS_COUNT];
    for(int i = 0; i < RES_TILE_SCORE_NUMBERS_COUNT; i++)
    {
        m_TileScoreNumbers[i] = OpenGLTextureCache::getInstance()->getTexture(RES_TILE_SCORE_NUMBERS[i]);
    }
}

Tile::~Tile()
{
    //Set the textures to NULL
    m_Texture = NULL;
    m_SelectedTile = NULL;

	// Delete the terrain damage texture
	if(m_DamagedTexture != NULL)
	{
		delete m_DamagedTexture;
		m_DamagedTexture = NULL;
	}

	// Delete the tower object
	if(m_Tower != NULL)
	{
		delete m_Tower;
		m_Tower = NULL;
	}
    
    //Delete the tile index number OpenGLTextures
    if(m_TileIndexNumbers != NULL)
    {
        for(int i = 0; i < RES_TILE_INDEX_NUMBERS_COUNT; i++)
        {
            m_TileIndexNumbers[i] = NULL;
        }
        
        //Lastly delete the array
        delete [] m_TileIndexNumbers;
        m_TileIndexNumbers = NULL;
    }
    
    //Delete the tile score number OpenGLTextures
    if(m_TileScoreNumbers != NULL)
    {
        for(int i = 0; i < RES_TILE_SCORE_NUMBERS_COUNT; i++)
        {
            m_TileScoreNumbers[i] = NULL;
        }
        
        //Lastly delete the array
        delete [] m_TileScoreNumbers;
        m_TileScoreNumbers = NULL;
    }
}

void Tile::update(double aDelta)
{
    // Update the tower object
	if(m_Tower != NULL)
	{
		m_Tower->update(aDelta);
	}
}

void Tile::paint()
{
    //Paint the texture if it is set
    if(m_Texture != NULL)
    {
        OpenGLRenderer::getInstance()->drawTexture(m_Texture, getX(), getY(), getWidth(), getHeight());
    }

	// Paint the terrain damage texture
	if(m_DamagedTexture != NULL)
	{
		// Only paint if the tile is damaged
		if(m_Damaged)
		{
			OpenGLRenderer::getInstance()->drawTexture(m_DamagedTexture, getX(), getY(), getWidth(), getHeight());
		}
	}

    //Paint the selected texture if this tile is actually selected
    if(isSelected() == true)
    {
        OpenGLRenderer::getInstance()->drawTexture(m_SelectedTile, getX(), getY(), getWidth(), getHeight());
    }

	// Paint the tower object
	if(m_Tower != NULL)
	{
		m_Tower->paint();
	}
}

void Tile::reset()
{
    m_IsSelected = false;
    m_IsPath = false;
	m_Damaged = false;

	// Reset the tower object
	if(m_Tower != NULL)
	{
		m_Tower->reset();
	}
}

void Tile::paintScore(OpenGLColor color, int scoreG, int scoreH, int scoreF)
{
    //Paint the color tile outline
    OpenGLRenderer::getInstance()->setLineWidth(2.0f);
    OpenGLRenderer::getInstance()->setForegroundColor(color);
    OpenGLRenderer::getInstance()->drawRectangle(getX(), getY(), getWidth(), getHeight(), false);
    OpenGLRenderer::getInstance()->setLineWidth(1.0f);

    //Get the scale, we get the smallest one for consistency
    float padding = 1.0f;
    float scale = fminf(getScoreNumberScale(scoreG, padding), fminf(getScoreNumberScale(scoreH, padding), getScoreNumberScale(scoreF, padding)));

    //Paint the scores
    paintScoreNumber(scoreG, BottomLeft, scale, padding);
    paintScoreNumber(scoreH, BottomRight, scale, padding);
    paintScoreNumber(scoreF, TopLeft, scale, padding);
}

void Tile::paintIndex(int aIndex)
{
    //Convert the index to a stringstream
    std::stringstream numberStream;
    numberStream << aIndex;
    
    //Next convert the stringstream into a string
    std::string numberString(numberStream.str());
    
    //Cycle through each number in the string and calculate the total width of the string
    float stringWidth = 0.0f;
    float stringHeight = 0.0f;
    for(int i = 0; i < numberString.length(); i++)
    {
        //Convert the letter in the string back to an int
        int index = atoi(numberString.substr(i,1).c_str());
        
        //Increment the X value
        stringWidth += m_TileIndexNumbers[index]->getSourceWidth();
        stringHeight = stringHeight < m_TileIndexNumbers[index]->getSourceHeight() ? m_TileIndexNumbers[index]->getSourceHeight() : stringHeight;
    }
    
    float padding = 4.0f;
    float scale = fminf((m_Width - padding) / stringWidth, 1.0f);
    float scaledWidth = stringWidth * scale;
    float scaledHeight = stringHeight * scale;
    
    //Calculate the x and y position based on the string width and height
    float x = getX() + (getWidth() - scaledWidth) / 2.0f;
    float y = getY() + (getHeight() - scaledHeight) / 2.0f;
    for(int i = 0; i < numberString.length(); i++)
    {
        //Convert the letter in the string back to an int
        int index = atoi(numberString.substr(i,1).c_str());
        
        //Calculate the scaled width and height
        float width = m_TileIndexNumbers[index]->getSourceWidth() * scale;
        float height = m_TileIndexNumbers[index]->getSourceHeight() * scale;
        
        //Draw the texture that is equivalent to the number
        OpenGLRenderer::getInstance()->drawTexture(m_TileIndexNumbers[index], x, y, width, height);
        
        //Increment the X value
        x += width;
    }
}

void Tile::paintScoreNumber(int number, ScoreNumberPosition position, float scale, float padding)
{
    //Check to see if its a walkable tile
    if(isWalkableTile() == true)
    {
        //Convert the number to a stringstream
        std::stringstream numberStream;
        numberStream << number;
        
        //Next convert the stringstream into a string
        std::string numberString(numberStream.str());
        
        //Cycle through each number in the string and calculate the total width of the string
        float stringWidth = 0.0f;
        float stringHeight = 0.0f;
        for(int i = 0; i < numberString.length(); i++)
        {
            //Convert the letter in the string back to an int
            int index = atoi(numberString.substr(i,1).c_str());
            
            //Increment the X value
            stringWidth += m_TileScoreNumbers[index]->getSourceWidth();
            stringHeight = stringHeight < m_TileScoreNumbers[index]->getSourceHeight() ? m_TileScoreNumbers[index]->getSourceHeight() : stringHeight;
        }
        
        float scaledWidth = stringWidth * scale;
        float scaledHeight = stringHeight * scale;
        float x = 0.0f;
        float y = 0.0f;
        
        //Calculate the x and y position based on the string width and height
        switch (position)
        {
            case TopLeft:
            x = getX() + padding;
            y = getY() + padding;
            break;

            case BottomLeft:
            x = getX() + padding;
            y = getY() + getHeight() - scaledHeight - padding;
            break;

            case BottomRight:
            x = getX() + getWidth() - scaledWidth - padding;
            y = getY() + getHeight() - scaledHeight - padding;
            break;
        }
        
        //Cycle through each number in the string and draw it
        for(int i = 0; i < numberString.length(); i++)
        {
            //Convert the letter in the string back to an int
            int index = atoi(numberString.substr(i,1).c_str());
            
            //Calculate the scaled width and height
            float width = m_TileScoreNumbers[index]->getSourceWidth() * scale;
            float height = m_TileScoreNumbers[index]->getSourceHeight() * scale;
            
            //Draw the texture that is equivalent to the number
            OpenGLRenderer::getInstance()->drawTexture(m_TileScoreNumbers[index], x, y, width, height);
            
            //Increment the X value
            x += m_TileScoreNumbers[index]->getSourceWidth() * scale;
        }
    }
}

float Tile::getScoreNumberScale(int number, float padding)
{
    //Convert the number to a stringstream
    std::stringstream numberStream;
    numberStream << number;
    
    //Next convert the stringstream into a string
    std::string numberString(numberStream.str());
    
    //Cycle through each number in the string and calculate the total width of the string
    float stringWidth = 0.0f;
    float stringHeight = 0.0f;
    for(int i = 0; i < numberString.length(); i++)
    {
        //Convert the letter in the string back to an int
        int index = atoi(numberString.substr(i,1).c_str());
        
        //Increment the X value
        stringWidth += m_TileScoreNumbers[index]->getSourceWidth();
        stringHeight = stringHeight < m_TileScoreNumbers[index]->getSourceHeight() ? m_TileScoreNumbers[index]->getSourceHeight() : stringHeight;
    }
    
    float scale = fminf(((m_Width - padding * 2.0f) / 2.0f) / stringWidth, 1.0f);
    return scale;
}

TileType Tile::getTileType()
{
    return m_TileType;
}

bool Tile::isWalkableTile()
{
    return m_IsWalkableTile;
}

void Tile::setIsSelected(bool aIsSelected)
{
	m_IsSelected = aIsSelected;
}

bool Tile::isSelected()
{
	return m_IsSelected;
}

void Tile::setIsPath(bool aIsPath)
{
    if(m_IsWalkableTile == true)
    {
        m_IsPath = aIsPath;
    }
}

bool Tile::isPath()
{
	return m_IsPath;
}

float Tile::getSpeedModifier()
{
	//TODO: change to constants
	switch(getTileType())
	{
	case TileTypeGround:
		return 1.0f;

	case TileTypeTree:
		return 1.0f;

	case TileTypeWater:
		return 0.25f;

	case TileTypeGrass:
		return 0.75f;

	case TileTypeBrick:
		return 1.25f;

	case TileTypeChest:
		return 1.0f;

	case TileTypeUnknown:
		return 1.0f;
	}
}

void Tile::setTower(Tower* tower)
{
	// If the tower pointer already points to a tower object, delete it
	if(m_Tower != NULL)
	{
		delete m_Tower;
		m_Tower = NULL;
	}

	// Set the new tower object to the m_Tower pointer
	m_Tower = tower;
}

Tower* Tile::getTower()
{
	return m_Tower;
}

void Tile::setHasTower(bool hasTurret)
{
	if(hasTurret)
	{
		m_IsWalkableTile = false;
	}
	else
	{
		m_IsWalkableTile = true;
	}
}