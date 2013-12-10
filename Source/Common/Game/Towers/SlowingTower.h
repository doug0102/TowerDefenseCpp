#ifndef SLOWING_TOWER_H
#define FLOWING_TOWER_H

#include "Tower.h"

class SlowingTower : public Tower
{
public:
	SlowingTower(Level* level);
	~SlowingTower();

	void paint();

	const char* getType();

protected:
	void handlePlayerCollision(Projectile* projectile);

	float m_Power;
};

#endif