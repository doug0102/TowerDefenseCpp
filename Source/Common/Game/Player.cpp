//
//  Player.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Player.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>

#include "Projectile.h"
#include "../Utils/Utils.h"

#include "PathNode.h"

Player::Player(Level* aLevel)
{
	// create a path finder object
	m_PathFinder = new PathFinder(aLevel, this);

    //Initialize the current and destination tiles to NULL
    m_CurrentTile = NULL;
    m_DestinationTile = NULL;
    
	// Intitialize the level member variable
	m_Level = aLevel;

	// intitialize the speed member variable
	m_Speed = PLAYER_SPEED;

	// Initialize the health
	m_Health = PLAYER_HEALTH_DEFAULT;

	// Initialize the power of projectiles
	m_Power = PLAYER_HEALTH_DEFAULT / 4;

	// Initialize the ammo
	m_Ammo = 3;

    //Initialize the animation member variables
    m_CanAnimate = false;
    m_AbortAnimation = false;
    m_AnimationPathNodeIndex = -1;

	m_IsHero = false;
    
    //Initialize the player's size
    setSize(PLAYER_SIZE, PLAYER_SIZE);
}

Player::~Player()
{
	if(m_PathFinder != NULL)
	{
		delete m_PathFinder;
		m_PathFinder = NULL;
	}

    //Set the current and desination tiles to NULL
	m_CurrentTile = NULL;
	m_DestinationTile = NULL;
}

void Player::update(double aDelta)
{
	// Update the projectile
	for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->update(aDelta);

		}
	}

	// Remove any 'inactive' projectiles from the vector
	int index = 0;
	while(index != m_Projectiles.size())
	{
		if(m_Projectiles.at(index)->getIsActive() == false)
		{
			//Log::debug("Deleting projectile");

			// Delete the projectile and remove it from the vector
			delete m_Projectiles.at(index);
			m_Projectiles.erase(m_Projectiles.begin() + index);
		}
		else
		{
			index++;
		}
	}


	// Update the pathfinder
	if(m_PathFinder->isSearchingPath() == true)
	{
		m_PathFinder->update(aDelta);
	}

	// Player animation
	if(isAnimating() == true && m_AnimationPathNodeIndex > -1)
	{
		PathNode* pathNode = m_PathFinder->getPathNodeAtIndex(m_AnimationPathNodeIndex);
		Tile* tile = pathNode != NULL ? pathNode ->getTile() : NULL;

		if(tile != NULL)
		{
			float centerX = tile->getX() + (tile->getWidth() - getWidth()) / 2.0f;
			float centerY = tile->getY() + (tile->getHeight() - getHeight()) / 2.0f;

			// calculate how much the player should animate
			float playerX = animate(getX(), centerX, aDelta);
			float playerY = animate(getY(), centerY, aDelta);
			setPosition(playerX, playerY);

			//has it reached the center of the tile?
			if(playerX == centerX && playerY == centerY)
			{
				m_AnimationPathNodeIndex++;

				m_CurrentTile->setIsPath(false);

				// Set the new current tile
				setCurrentTile(tile);

				//Are we done animating?
				if(m_AnimationPathNodeIndex >= m_PathFinder->getPathSize())
				{
					stopAnimating();
					m_CurrentTile->setIsPath(false);
				}

				//is the abort animation flag set?
				if(m_AbortAnimation == true)
				{
					// Reset the flag to false
					m_AbortAnimation = false;

					// begin searching the new path
					findPath();
				}

			}
		}
	}
}

void Player::paint()
{
	// Cycle through and paint all the projectiles
	for(int i = 0; i < m_Projectiles.size(); i++)
	{
		// Only paint active projectiles
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}

	// Paint the player
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_INSIDE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2);

	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false);

	// Paint the player's health
	m_Level->drawNumber(m_Health, getX(), getY());
}

void Player::reset()
{
	// Stop animating the player
	stopAnimating();

	// Reset the path finder
	m_PathFinder->reset();

	// Set the destination tile to NULL
    m_DestinationTile = NULL;

	// Set the player's state to 'active'
	setIsActive(true);

	// Reset the health of the player
	m_Health = PLAYER_HEALTH_DEFAULT;

	// Initialize the power of projectiles
	m_Power = PLAYER_HEALTH_DEFAULT / 4;

	// Reset the player's ammo
	m_Ammo = 3;
}

void Player::fireProjectile(float x, float y)
{
	if( m_Ammo > 0)
	{
		// Infinate ammo for now
		//m_Ammo--;

		// Create the projectile object
		// Does 25 damage, default player health / 4, default health is 100
		// Projectile speed set to 500.0f, multiplied by the level's speed modification
		Projectile* projectile = new  Projectile(this, m_Power, 500.0f * m_Level->m_LevelSpeed);
		projectile->setPosition(getX() + (getWidth() / 2.0f), getY() + (getHeight() / 2.0f));
		projectile->setTarget(x, y);
		m_Projectiles.push_back(projectile);

		//Log::debug("Fired projectile, %i ammo left", m_Ammo);
	}
	else
	{
		//Log::debug("Can't fire. no ammo left");
	}
}

void Player::applyDamage(int damage)
{
	m_Health -= damage;

	if(m_Health <= 0)
	{
		m_Health = 0;
		setIsActive(false);

		// Damage the tile 
		m_Level->getTileForIndex(m_Level->getTileIndexForPlayer(this))->m_Damaged = true;

		// If an enemy died, increase the player's currency
		if(getType() == ENEMY_TYPE)
		{
			if(m_Level != NULL)
			{
				// Only reward the player for a kill if the enemy didn't die from reaching their destination
				if(m_CurrentTile != m_DestinationTile)
				{
					m_Level->m_Currency += ENEMY_DEFAULT_BOUNTY;
					m_Level->m_Score++;
				}
			}
		}

		//Log::debug("Player is dead.");
	}
	else
	{
		//Log::debug("Player is hit, %i health remaining.", m_Health);
	}
}

void Player::handleBoundsCollision(Projectile* projectile)
{
	Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());

	if(tile == NULL)
	{
		projectile->setIsActive(false);

		//Log::debug("Projectile went off screen");
	}
}

void Player::setCurrentTile(Tile* tile)
{
	//Set the current tile pointer
	m_CurrentTile = tile;
    
	//Center the player's position on the tile
	setPosition(tile->getX() + ((tile->getWidth() - getWidth()) / 2), tile->getY() + ((tile->getHeight() - getHeight()) / 2));
}

void Player::setDestinationTile(Tile* tile)
{
	//Set the destination tile pointer
	m_DestinationTile = tile;

	//start pathfinding
	if(isAnimating() == false)
	{
		findPath();
	}
	else
	{
		m_AbortAnimation = true;
	}
}

void Player::pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound)
{
	if(pathFinder == m_PathFinder)
	{
		if(pathWasFound == true)
		{
			startAnimating();
		}
		else
		{
			m_PathFinder->reset();
		}
	}
}

PathFinder* Player::getPathFinder()
{
	return m_PathFinder;
}

void Player::findPath()
{
	m_PathFinder->reset();
	m_PathFinder->findPath(m_CurrentTile, m_DestinationTile);
}

float Player::animate(float aCurrent, float aTarget, double aDelta)
{
	// Animates the player movement. The speed is modified by the tile it's on and the level's speed.
    float increment = aDelta * m_Speed * m_CurrentTile->getSpeedModifier() * (aTarget < aCurrent ? -1 : 1) * m_Level->m_LevelSpeed;

    if(fabs(increment) > fabs(aTarget - aCurrent))
    {
        return aTarget;
    }
    else
    {
        aCurrent += increment;
    }
    return aCurrent;
}

void Player::startAnimating()
{
	m_CanAnimate = true;
	m_AnimationPathNodeIndex = 0;
}

void Player::stopAnimating()
{
	m_CanAnimate = false;
	m_AnimationPathNodeIndex = -1;
}

bool Player::isAnimating()
{
    return m_CanAnimate;
}
