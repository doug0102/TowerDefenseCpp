#include "SlowingTower.h"
#include "../Level.h"
#include "../Tiles/Tile.h"
#include "../Enemy.h"
#include "../../OpenGL/OpenGL.h"

SlowingTower::SlowingTower(Level* level) : Tower(TowerTypeTurret, level)
{
	m_Texture = new OpenGLTexture("broccoli");
	setSize(TOWER_WIDTH, TOWER_HEIGHT);
	m_Speed = TOWER_SLOWING_SPEED;
	m_Power = TOWER_SLOWING_DAMAGE;
	m_Range = TOWER_SLOWING_RANGE;
}

SlowingTower::~SlowingTower()
{
	if(m_Texture != NULL)
	{
		delete m_Texture;
		m_Texture = NULL;
	}
}

void SlowingTower::paint()
{
	Tower::paint();

	if(m_Texture != NULL)
	{
		OpenGLRenderer::getInstance()->drawTexture(m_Texture, getX(), getY(), getWidth(), getHeight(), m_Angle);
	}
}

const char* SlowingTower::getType()
{
	return TOWER_SLOWING_TYPE;
}

void SlowingTower::handlePlayerCollision(Projectile* projectile)
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
				enemy->slowEnemy(1.5, m_Power);
				projectile->setIsActive(false);
			}
		}
	}
}