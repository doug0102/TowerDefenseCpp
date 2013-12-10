//
//  BrickTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "BrickTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


BrickTile::BrickTile(const char* textureName) : Tile(TileTypeBrick, textureName, true)
{
	m_IsWalkableTile = true;
}

BrickTile::~BrickTile()
{

}

const char* BrickTile::getType()
{
    return TILE_BRICK_TYPE;
}