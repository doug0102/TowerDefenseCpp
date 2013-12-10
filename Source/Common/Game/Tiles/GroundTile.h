//
//  GroundTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef GROUND_TILE_H
#define GROUND_TILE_H

#include "Tile.h"


class GroundTile : public Tile
{
public:
	GroundTile(const char* textureName = RES_TILE_GROUND);
	virtual ~GroundTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif
