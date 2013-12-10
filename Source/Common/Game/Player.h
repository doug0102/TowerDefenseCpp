//
//  Player.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "PathFinder.h"
#include "Projectile.h"
#include <vector>

class Level;
class Tile;
class Projectile;

class Player : public GameObject, public PathFinderListener, public ProjectileListener
{
public:
	Player(Level* level);
	virtual ~Player();

	//Update, paint and reset methods
	void update(double delta);
	void paint();
	void reset();

	//Keep GameObject's pure virtual function, making Player an abstract class
	virtual const char* getType() = 0;

	//Setter methods for the current and destination tiles
	void setCurrentTile(Tile* tile);
	void setDestinationTile(Tile* tile);

	// Projectile methods
	void fireProjectile(float x, float y);
	void applyDamage(int damage);

protected:
	// ProjectileListener methods
	virtual void handlePlayerCollision(Projectile* projectile) = 0;
	virtual void handleBoundsCollision(Projectile* projectile);

	//pathfinderlistener method
	virtual void pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound);

	// path finder methods
	PathFinder* getPathFinder();
	void findPath();

	//Animation methods
	float animate(float current, float target, double delta);
	void startAnimating();
	void stopAnimating();
	bool isAnimating();

	// Friend class Level so that it can access the protected members
	friend class Level;

	// path finding variables
	PathFinder* m_PathFinder;
	Tile* m_CurrentTile;
	Tile* m_DestinationTile;
	Level* m_Level;
	bool m_CanAnimate;
	bool m_AbortAnimation;
	int m_AnimationPathNodeIndex;
	
	// The speed of the player
	float m_Speed;

	// The power of the player's projectiles (damage)
	int m_Power;

	// The player's health
	int m_Health;
	int m_Ammo;

	// The player's projectiles
	std::vector<Projectile*> m_Projectiles;

	bool m_IsHero;
};

#endif