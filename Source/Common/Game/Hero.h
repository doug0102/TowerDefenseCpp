#include "Player.h"

class Hero : public Player
{
public:
	Hero(Level* level);
	~Hero();

	void paint();

	const char* getType();

	void mouseLeftClickUpEvent(float positionX, float positionY);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void keyUpEvent(int keyCode);

protected:
	void handlePlayerCollision(Projectile* projectile);
};