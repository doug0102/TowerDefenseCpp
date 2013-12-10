#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../OpenGL/OpenGLColor.h"

//Game Constants
extern const char* GAME_SCREEN_NAME;
extern const int GAME_STARTING_CURRENCY;
extern const float GAME_DEFAULT_SPEED;
extern const int GAME_MAX_SCORE_DEFAULT;
extern const int GAME_STARTING_LIVES;
extern const int GAME_MAX_LIVES;
extern const double GAME_TIME_LIMIT_DEFAULT;

//Tile Constants
extern const char* TILE_GROUND_TYPE;
extern const char* TILE_TREE_TYPE;
extern const char* TILE_WATER_TYPE;
extern const char* TILE_GRASS_TYPE;
extern const char* TILE_BRICK_TYPE;
extern const char* TILE_CHEST_TYPE;
extern const int TILE_PADDING;

extern const int TILE_GROUND_COST;
extern const int TILE_TREE_COST;
extern const int TILE_WATER_COST;
extern const int TILE_GRASS_COST;

//Player Constants
extern const int PLAYER_SIZE;
extern const float PLAYER_SPEED;
extern const float PLAYER_MIN_SPEED;
extern const float PLAYER_MAX_SPEED;
extern const int PLAYER_HEALTH_DEFAULT;
extern const int PLAYER_HEALTH_MAX;
extern const OpenGLColor PLAYER_INSIDE_COLOR;
extern const OpenGLColor PLAYER_OUTLINE_COLOR;

// Hero constants
extern const char* HERO_TYPE;

// Enemy constants
extern const char* ENEMY_TYPE;
extern const int ENEMY_COUNT;
extern const int ENEMY_DEFAULT_HEALTH;
extern const int ENEMY_DEFAULT_BOUNTY;
extern const int ENEMY_DEFAULT_SCORE;
extern const float ENEMY_SPEED_EASY;
extern const float ENEMY_SPEED_NORMAL;
extern const float ENEMY_SPEED_HARD;

// projetile constants
extern const char* PROJECTILE_TYPE_DEFAULT;

// Tower constants
extern const int TOWER_UPGRADE_COST;
extern const int TOWER_MAX_UPGRADES;
extern const float TOWER_WIDTH;
extern const float TOWER_HEIGHT;

extern const char* TOWER_TURRET_TYPE;
extern const int TOWER_TURRET_COST;
extern const double TOWER_TURRET_RANGE;
extern const float TOWER_TURRET_SPEED;
extern const int TOWER_TURRET_DAMAGE;

extern const char* TOWER_SLOWING_TYPE;
extern const int TOWER_SLOWING_COST;
extern const double TOWER_SLOWING_RANGE;
extern const float TOWER_SLOWING_SPEED;
extern const int TOWER_SLOWING_DAMAGE;

#endif 