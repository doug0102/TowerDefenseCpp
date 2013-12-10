//
//  GroundTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GroundTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


GroundTile::GroundTile(const char* textureName) : Tile(TileTypeGround, textureName, true)
{
	m_IsWalkableTile = true;
}

GroundTile::~GroundTile()
{

}

const char* GroundTile::getType()
{
    return TILE_GROUND_TYPE;
}
