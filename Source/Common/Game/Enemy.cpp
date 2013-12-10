#include "Enemy.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "Hero.h"
#include "../Constants/Constants.h"
#include "../OpenGL/OpenGLColor.h"

#include "../Input/Input.h"
#include "../Utils/Utils.h"

Enemy::Enemy(Level* level, float speed) : Player(level)
{
	m_ShootingTimer = 0.0;
	m_SlowTimer = 0.0;
	m_Speed = speed;
	m_Power = PLAYER_HEALTH_DEFAULT / 20;
	m_PreviousSpeed = m_Speed;
}

Enemy::~Enemy()
{

}

const char* Enemy::getType()
{
	return ENEMY_TYPE;
}

void Enemy::update(double delta)
{
	if(m_SlowTimer > 0.0)
	{
		m_SlowTimer -= delta;
		if(m_SlowTimer < 0.0)
		{
			m_Speed = m_PreviousSpeed;
			m_SlowTimer = 0.0;
		}
	}

	// Increment the shooting timer
	m_ShootingTimer += delta;

	Player::update(delta);

	// If the enemy has reached the destination
	if(m_CurrentTile == m_DestinationTile)
	{
		// Apply fatal damage to this enemy
		Player::applyDamage(m_Health);

		// The player loses 1 life
		m_Level->m_Lives = m_Level->m_Lives - 1;
	}

	// Shoot a projectile if enough time has passed
	// Shoots every 2.5 seconds
	if(m_ShootingTimer >= 2.5)
	{
		Tile* targetTile = m_Level->getTileForHero();
		float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
		float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);

		// Fire the projectile
		//fireProjectile(centerX, centerY);

		// Reset the shooting timer
		m_ShootingTimer = 0.0;
	}
}

void Enemy::paint()
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

	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2);
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlack());
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, false);

	// Draw the enemy health
	m_Level->drawNumber(m_Health, getX(), getY());
}

void Enemy::reset()
{
	// Call the base class' reset method
	Player::reset();

	if(m_Level != NULL)
	{
		// Set the destination tile
		if(m_Level->getTileForChest() != NULL)
		{
			// Enemies will target the chest tile by default
			setDestinationTile(m_Level->getTileForChest());
		}
		else
		{
			if(m_Level->getTileForPlayer(m_Level->getHero()) != NULL)
			{
				// If no chest tile is found, target the player
				setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
			}
		}

		int round = m_Level->m_Round;

		// Set the speed and health 
		if(m_Level->m_Difficulty == 1)
		{
			m_Health = ENEMY_DEFAULT_HEALTH + (10 * round);
			m_Speed = ENEMY_SPEED_EASY + (2 * round);
		}
		else if(m_Level->m_Difficulty == 2)
		{
			m_Health = (ENEMY_DEFAULT_HEALTH * 1.25) + (15 * round);
			m_Speed = ENEMY_SPEED_NORMAL + (4 * round);
		}
		else if(m_Level->m_Difficulty == 3)
		{
			m_Health = (ENEMY_DEFAULT_HEALTH * 1.5) + (20 * round);
			m_Speed = ENEMY_SPEED_HARD + (6 * round);
		}
	}

	m_ShootingTimer = 0.0;
	m_SlowTimer = 0.0;
}

void Enemy::fireProjectile(float x, float y)
{
	if( m_Ammo > 0)
	{
		// Infinate ammo, but enemies do not shoot for now.

		// Create the projectile object
		Projectile* projectile = new  Projectile(this, m_Power, 150.0f * m_Level->m_LevelSpeed);
		projectile->setPosition(getX() + (getWidth() / 2.0f), getY() + (getHeight() / 2.0f));
		projectile->setTarget(x, y);
		m_Projectiles.push_back(projectile);
	}
}

void Enemy::slowEnemy(double length, float power)
{
	// Don't slow if the enemy is already slowed
	if(m_SlowTimer != 0.0)
	{
		return;
	}

	if(length > 0.0 && power > 0)
	{
		// Maximum length of 3 seconds
		if(length > 3.0)
		{
			length = 3.0;
		}

		// Can't slow down to less than a 5th of their speed
		if(power > m_Speed / 5)
		{
			power = m_Speed / 5;
		}

		m_PreviousSpeed = m_Speed;

		m_SlowTimer = length;
		m_Speed /= power;
	}
}

void Enemy::handlePlayerCollision(Projectile* projectile)
{
	Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
	Hero* hero = m_Level->getHero();

	if(hero != NULL && hero->getIsActive() == true)
	{
		// Get the tile the hero is on
		Tile* heroTile = m_Level->getTileForPlayer(hero);

		// Is the projectile on the same tile as the hero
		if(tile == heroTile)
		{
			// Apply damage to the hero and set the propjectile to inactive
			hero->applyDamage(projectile->getDamage());
			projectile->setIsActive(false);
		}
	}
}