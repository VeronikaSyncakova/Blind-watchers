#pragma once

#include <SFML/Graphics.hpp>
#include "CollisionObserver.hpp"

struct Bullet
{
	void update();

	std::shared_ptr<sf::CircleShape> m_bullet;
	sf::Vector2f m_displacement;
	bool m_active;
	int m_damage{ 20 };
};

struct collisionInfo
{
	Bullet collidingBullet;
	sf::FloatRect collidedNPC;
};

#include "ParticleSpawner.hpp"

class ParticleSpawnerObserver : public npcCollisionObserver
{
public:
	void listen(collisionInfo& t_bulletInfo)override
	{
		ParticleSpawner::spawnBlood(t_bulletInfo.collidingBullet.m_displacement, t_bulletInfo.collidingBullet.m_bullet->getPosition());
	}
};

class damageApplicator;

class BulletHolder : public ObserverSubjectTemplate<npcCollisionObserver>
{
public:
	BulletHolder();
	~BulletHolder();

	void assignDamageApplicator(std::shared_ptr<damageApplicator> t_newObserver);

	void update();
	void spawnNewBullet(sf::Vector2f t_loc, sf::Vector2f t_target);
	void checkCollisions(sf::FloatRect t_bounds);
	void checkWallCollision(int t_roomNum);
private:
	std::vector<Bullet> m_bullets;
};
