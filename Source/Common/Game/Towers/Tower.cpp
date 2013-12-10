#include "Tower.h"
#include "../Enemy.h"
#include "../Level.h"
#include "../Tiles/Tile.h"
#include <math.h>

Tower::Tower(TowerType towerType, Level* level) : Player(level),
m_TowerType(towerType)
{
	m_Target = NULL;
	m_ShootingTimer = 0.0;
	m_Range = 0.0;
	m_Speed = 0.0;
	m_Power = 0;
	m_Angle = 0.0f;
	m_NumberOfUpgrades = 0;
}

Tower::~Tower()
{
	m_Target = NULL;
}

void Tower::update(double delta)
{
	// Increment the shooting timer
	m_ShootingTimer += delta;

	Player::update(delta);

	if(m_Level != NULL)
	{
		if(m_Target != NULL && m_Target->getIsActive())
		{
			// Shoot a projectile if enough time has passed
			if(m_ShootingTimer >= m_Speed)
			{
				Tile* targetTile = m_Level->getTileForIndex( m_Level->getTileIndexForPlayer(m_Target) );

				float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
				float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);

				// Fire the projectile
				fireProjectile(centerX, centerY);

				// Reset the shooting timer
				m_ShootingTimer = 0.0;
			}

			// Rotate the tower to follow enemies
			float angle = atan2(getY() - m_Target->getY(), getX() - m_Target->getX());
			m_Angle = angle * 180 / 3.141592;

			// Check to see if the target is still within range
			checkTargetRange(m_Target);
		}
		else
		{
			// Find a targe twithin range
			findTarget();
		}

		// Set the tile's walkable state (the tower's tile location)
		Tile* tile = m_Level->getTileForIndex(m_Level->getTileIndexForPosition(getX(), getY()));

		if(tile != NULL && tile->isWalkableTile())
		{
			tile->setHasTower(true);

			// Go through all the active enemies
			for(int i = 0; i < m_Level->m_Enemies.size(); i++)
			{
				Enemy* enemy = m_Level->m_Enemies.at(i);

				if(enemy != NULL && enemy->getIsActive())
				{
					if(m_Level->getTileForChest() != NULL)
					{
						// Update their pathfinding
						enemy->setDestinationTile(m_Level->getTileForChest());
					}
				}
			}
		}
	}
}

void Tower::paint()
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
}

void Tower::reset()
{
	m_Target = NULL;
}

TowerType Tower::getTowerType()
{
	return m_TowerType;
}

void Tower::fireProjectile(float x, float y)
{
	Projectile* projectile = new Projectile(this, m_Power, 500.0f * m_Level->m_LevelSpeed);
	projectile->setPosition(getX() + (getWidth() / 2.0f), getY() + (getHeight() / 2.0f));
	projectile->setTarget(x, y);
	m_Projectiles.push_back(projectile);
}

void Tower::handlePlayerCollision(Projectile* projectile)
{
	Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());

	// Cycle through all the enemies and check for colision with the projectile
	for(int i = 0; i < m_Level->getEnemies().size(); i++)
	{
		Enemy* enemy = m_Level->getEnemies().at(i);
		if(enemy != NULL && enemy->getIsActive() == true)
		{
			// Get the tile the enemy is on
			Tile* enemyTile = m_Level->getTileForPlayer(enemy);

			// Is the projectile on the same tile as the enemy
			if(tile == enemyTile)
			{
				// Apply damage to the enemy and set the propjectile to inactive
				enemy->applyDamage(projectile->getDamage());
				projectile->setIsActive(false);
			}
		}
	}
}

void Tower::findTarget()
{
	std::vector<Enemy*> enemies = m_Level->getEnemies();

	double closest = m_Range;

	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies.at(i)->getIsActive())
		{
			// Calculate the distance
			double dx = (enemies.at(i)->getX() - getX());
			double dy = (enemies.at(i)->getY() - getY());
			double distance = sqrt(dx * dx + dy * dy);

			if(distance <= closest)
			{
				closest = distance;
				if(closest != m_Range)
				{
					// Target the closest enemy within range
					m_Target = enemies.at(i);
				}
			}
		}
	}
}

void Tower::checkTargetRange(Enemy* target)
{
	if(target != NULL)
	{
		// Calculate the distance
		double dx = (target->getX() - getX());
		double dy = (target->getY() - getY());
		double distance = sqrt(dx * dx + dy * dy);

		// If the target is out of range
		if(distance > m_Range)
		{
			// Set the target to NULL, update will loop the findTarget function
			m_Target = NULL;
		}
	}
}

void Tower::paintTowerRange()
{
	if(m_Target == NULL)
	{
		OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
	}
	else
	{
		if(m_Target->getIsActive())
		{
			OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
		}
		else
		{
			OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
		}
	}

	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), m_Range, false);
}