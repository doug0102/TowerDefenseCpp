// Projectile.h
// Shea Dougherty-Gill

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class ProjectileListener;

class Projectile : public GameObject
{
public:

	Projectile(ProjectileListener* listener, int damage, float velocity);
	virtual ~Projectile();

	virtual void update(double delta);
	virtual void paint();
	virtual void reset();

	virtual const char* getType();

	virtual void setTarget(float x, float y);
	virtual int getDamage();

protected:

	ProjectileListener* m_Listener;

	int m_Damage;
	float m_Velocity;
	float m_Angle;
	float m_TargetX;
	float m_TargetY;
};


class ProjectileListener
{
public:
	virtual void handlePlayerCollision(Projectile* projectile) = 0;
	virtual void handleBoundsCollision(Projectile* projectile) = 0;
};

#endif