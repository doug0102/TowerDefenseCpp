//
//  ChestTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "ChestTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"

ChestTile::ChestTile(const char* textureName) : Tile(TileTypeChest, textureName, true)
{
	m_IsWalkableTile = true;
}

ChestTile::~ChestTile()
{

}

const char* ChestTile::getType()
{
	return TILE_CHEST_TYPE;
}