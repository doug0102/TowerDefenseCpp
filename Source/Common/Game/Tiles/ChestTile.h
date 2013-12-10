//
//  ChestTile.h
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef CHEST_TILE_H
#define CHEST_TILE_H

#include "Tile.h"

class ChestTile : public Tile
{
public:
	ChestTile(const char* textureName = RES_TILE_CHEST);
	virtual ~ChestTile();

	// return the type of file
	const char* getType();
};

#endif