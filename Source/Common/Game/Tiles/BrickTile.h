//
//  BrickTile.h
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef BRICK_TILE_H
#define BRICK_TILE_H

#include "Tile.h"


class BrickTile : public Tile
{
public:
	BrickTile(const char* textureName = RES_TILE_BRICK);
	virtual ~BrickTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif