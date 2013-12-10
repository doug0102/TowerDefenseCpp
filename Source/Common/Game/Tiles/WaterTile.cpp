//
//  WaterTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "WaterTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


WaterTile::WaterTile(const char* textureName) : Tile(TileTypeWater, textureName, true)
{
	m_IsWalkableTile = false;
}

WaterTile::~WaterTile()
{

}

const char* WaterTile::getType()
{
    return TILE_WATER_TYPE;
}