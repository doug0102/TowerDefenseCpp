//
//  TreeTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Shea Dougherty-Gill
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "TreeTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


TreeTile::TreeTile(const char* textureName) : Tile(TileTypeTree, textureName, true)
{
	m_IsWalkableTile = false;
}

TreeTile::~TreeTile()
{

}

const char* TreeTile::getType()
{
    return TILE_TREE_TYPE;
}