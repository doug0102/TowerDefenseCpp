#include "GameConstants.h"


//Game Constants
const char* GAME_SCREEN_NAME = "Game";
const int GAME_STARTING_CURRENCY = 5000;
const float GAME_DEFAULT_SPEED = 1.0f;
const int GAME_MAX_SCORE_DEFAULT = 10000;
const int GAME_STARTING_LIVES = 3;
const int GAME_MAX_LIVES = 6;
const double GAME_TIME_LIMIT_DEFAULT = 120.0;

//Tiles Constants
const char* TILE_GROUND_TYPE = "GroundTile";
const char* TILE_TREE_TYPE = "TreeTile";
const char* TILE_WATER_TYPE = "WaterTile";
const char* TILE_GRASS_TYPE = "GrassTile";
const char* TILE_BRICK_TYPE = "BrickTile";
const char* TILE_CHEST_TYPE = "ChestTile";
const int TILE_PADDING = 2;

const int TILE_GROUND_COST = 100;
const int TILE_TREE_COST = 1000;
const int TILE_WATER_COST = 500;
const int TILE_GRASS_COST = 250;

//Player Constants
const int PLAYER_SIZE = 24;
const float PLAYER_SPEED = 150.0f;
const float PLAYER_MIN_SPEED = 50.0f;
const float PLAYER_MAX_SPEED = 300.0f;
const int PLAYER_HEALTH_DEFAULT = 100;
const int PLAYER_HEALTH_MAX = 1000;
const OpenGLColor PLAYER_INSIDE_COLOR = OpenGLColor(0.0f, 0.0f, 0.0f, 1.0f);
const OpenGLColor PLAYER_OUTLINE_COLOR = OpenGLColor(1.0f, 1.0f, 1.0f, 1.0f);

// Hero constants
const char* HERO_TYPE = "Hero";

// Enemy constants
const char* ENEMY_TYPE = "Enemy";
const int ENEMY_COUNT = 10;
const int ENEMY_DEFAULT_HEALTH = 100;
const int ENEMY_DEFAULT_BOUNTY = 100;
const int ENEMY_DEFAULT_SCORE = 10;
const float ENEMY_SPEED_EASY = 35.0f;
const float ENEMY_SPEED_NORMAL = 50.0f;
const float ENEMY_SPEED_HARD = 75.0f;

// projetile constants
const char* PROJECTILE_TYPE_DEFAULT = "DefaultProjectile";

// Tower constants
const int TOWER_UPGRADE_COST = 350;
const int TOWER_MAX_UPGRADES = 5;
const float TOWER_WIDTH = 35.0f;
const float TOWER_HEIGHT = 35.0f;

const char* TOWER_TURRET_TYPE = "TurretTower";
const int TOWER_TURRET_COST = 1000;
const double TOWER_TURRET_RANGE = 75.0;
const float TOWER_TURRET_SPEED = 0.35f;
const int TOWER_TURRET_DAMAGE = 20;

const char* TOWER_SLOWING_TYPE = "SlowingTower";
const int TOWER_SLOWING_COST = 1500;
const double TOWER_SLOWING_RANGE = 150.0;
const float TOWER_SLOWING_SPEED = 2.0f;
const int TOWER_SLOWING_DAMAGE = 2.0;
