//
//  LevelConstants.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_CONSTANTS_H
#define LEVEL_CONSTANTS_H

//Global enum for the Level's tile types,
//add additional tile types in this enum
enum TileType
{
  TileTypeGround = 1,	// (0000 0001)
  TileTypeTree = 2,		// (0000 0010)
  TileTypeWater = 4,	// (0000 0100)
  TileTypeGrass = 8,	// (0000 1000)
  TileTypeBrick = 16,   // (0001 0000)
  TileTypeChest = 32,	// (0010 0000)	
  TileTypeUnknown = -1,
  TileTypeCount = 6
};

enum TowerType
{
	TowerTypeTurret = 64,	// (0100 0000)
	TowerTypeSlowing = 128,

	// Count value must be updated when a new turret is added
	TowerTypeCount = 2,
	TowerTypeUnknown
};

//Level editor screen name
extern const char* LEVEL_EDITOR_SCREEN_NAME;

//Empty Level Constants
extern const int EMPTY_LEVEL_TILE_SIZE;
extern const int EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX;

#endif
