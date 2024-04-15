#pragma once

#include <SFML/Graphics.hpp>
#include "CollisionObserver.hpp"

struct Bullet
{
	void update();

	std::shared_ptr<sf::CircleShape> m_bullet;
	sf::Vector2f m_displacement;
	bool m_active;
};

#include "ParticleSpawner.hpp"

class ParticleSpawnerObserver : public npcCollisionObserver
{
public:
	void listen(Bullet& t_bullet)override
	{
		ParticleSpawner::spawnBlood(t_bullet.m_displacement, t_bullet.m_bullet->getPosition());
	}
};

class BulletHolder : public ObserverSubjectTemplate<npcCollisionObserver>
{
public:
	BulletHolder();
	~BulletHolder();

	void update();
	void spawnNewBullet(sf::Vector2f t_loc, sf::Vector2f t_target);
	void checkCollisions(sf::FloatRect t_bounds);
private:
	std::vector<Bullet> m_bullets;
};
