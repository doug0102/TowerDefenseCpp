//
//  Tile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef TILE_H
#define TILE_H

#include "../GameObject.h"
#include "../../Constants/Constants.h"
#include <stdlib.h>


class OpenGLTexture;
class Tower;

class Tile : public GameObject
{
public:
    //Tile takes on parameter, whether it can be walked on or not
	Tile(TileType tileType, const char* tileTexture, bool isWalkableTile);
	virtual ~Tile();
    
    //Update, Paint and reset methods
	virtual void update(double delta);
	virtual void paint();
    virtual void reset();
    
    //Paint methods to draw the tile score, drawn from the PathFinding class
    virtual void paintScore(OpenGLColor color, int scoreG, int scoreH, int scoreF);
    
    //Paint method to draw the tile's index, drawn from the Level class
    virtual void paintIndex(int index);
    
    //Pure virtual method inerited from GameObject
    virtual const char* getType() = 0;
    
    //
    virtual TileType getTileType();
    
    //Is this a walkable tile, can the user walk on the tile
    virtual bool isWalkableTile();
    
    //Sets wether the tile is selected or not
    virtual void setIsSelected(bool isSelected);
	virtual bool isSelected();
    
    //Sets wether the tile is a path or not
	virtual void setIsPath(bool isPath);
	virtual bool isPath();

	// Gets the tile's speed modifier
	virtual float getSpeedModifier();

	virtual void setTower(Tower* tower);
	virtual Tower* getTower();

	virtual void setHasTower(bool hasTurret);
    
protected:

	friend class Player;
	friend class Level;
	friend class Tower;
	friend class Game;

    enum ScoreNumberPosition
    {
        TopLeft = 0,
        BottomLeft,
        BottomRight
    };

    //Conveniance method to paint a score number and a certain position
    void paintScoreNumber(int number, ScoreNumberPosition position, float scale, float padding);
    float getScoreNumberScale(int number, float padding);
    
    //Member variables
    TileType m_TileType;
    bool m_IsWalkableTile;
    bool m_IsSelected;
	bool m_IsPath;
    OpenGLTexture* m_SelectedTile;
    OpenGLTexture** m_TileIndexNumbers;
    OpenGLTexture** m_TileScoreNumbers;

	OpenGLTexture* m_DamagedTexture;
	bool m_Damaged;

	Tower* m_Tower;
};

#endif
