#include "Player.h"

class Enemy : public Player
{
public: 
	Enemy(Level* level, float speed);
	virtual ~Enemy();

	const char* getType();

	void update(double delta);
	void paint();
	void reset();

	void fireProjectile(float x, float y);

	void slowEnemy(double length, float power);

protected:
	void handlePlayerCollision(Projectile* projectile);

	double m_ShootingTimer;
	double m_SlowTimer;
	double m_PreviousSpeed;
};