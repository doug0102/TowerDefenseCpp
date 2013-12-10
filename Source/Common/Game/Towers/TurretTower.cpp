#include "TurretTower.h"
#include "../../OpenGL/OpenGL.h"

TurretTower::TurretTower(Level* level) : Tower(TowerTypeTurret, level)
{
	m_Texture = new OpenGLTexture("Turret");
	setSize(TOWER_WIDTH, TOWER_HEIGHT);
	m_Speed = TOWER_TURRET_SPEED;
	m_Power = TOWER_TURRET_DAMAGE;
	m_Range = TOWER_TURRET_RANGE;
}

TurretTower::~TurretTower()
{
	if(m_Texture != NULL)
	{
		delete m_Texture;
		m_Texture = NULL;
	}
}

void TurretTower::paint()
{
	Tower::paint();

	if(m_Texture != NULL)
	{
		OpenGLRenderer::getInstance()->drawTexture(m_Texture, getX(), getY(), getWidth(), getHeight(), m_Angle);
	}
}

const char* TurretTower::getType()
{
	return TOWER_TURRET_TYPE;
}