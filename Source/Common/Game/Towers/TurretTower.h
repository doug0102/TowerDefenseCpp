#ifndef TURRET_TOWER_H
#define TURRET_TOWER_H

#include "Tower.h"

class TurretTower : public Tower
{
public:
	TurretTower(Level* level);
	~TurretTower();

	void paint();

	const char* getType();
};

#endif