//
//  GrassTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GrassTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


GrassTile::GrassTile(const char* textureName) : Tile(TileTypeGrass, textureName, true)
{
	m_IsWalkableTile = true;
}

GrassTile::~GrassTile()
{

}

const char* GrassTile::getType()
{
    return TILE_GRASS_TYPE;
}