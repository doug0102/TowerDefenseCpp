#ifndef TOWER_H
#define TOWER_H

#include "../Player.h"
#include "../../Constants/Constants.h"

class Enemy;

class Tower : public Player
{
public:
	Tower(TowerType towerType, Level* level);
	virtual ~Tower();

	virtual void update(double delta);
	virtual void paint();
	virtual void reset();

	virtual const char* getType() = 0;

	virtual TowerType getTowerType();

	void fireProjectile(float x, float y);

	void findTarget();
	void checkTargetRange(Enemy* target);

	void paintTowerRange();

protected:

	friend class Game;

	virtual void handlePlayerCollision(Projectile* projectile);

	TowerType m_TowerType;

	Enemy* m_Target;

	double m_Range;
	int m_NumberOfUpgrades;
	double m_ShootingTimer;
	float m_Angle;
};

#endif