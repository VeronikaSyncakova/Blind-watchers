#include "Bullet.h"
#include "Game.h"
#include "RenderObject.h"
#include "simpleMaths.h"
#include "DamageApplicator.hpp"

BulletHolder::BulletHolder()
{
	std::shared_ptr<ParticleSpawnerObserver> t;
	t = std::make_shared< ParticleSpawnerObserver>();
	AddObserver(t);
}

BulletHolder::~BulletHolder()
{
}

void BulletHolder::assignDamageApplicator(std::shared_ptr<damageApplicator> t_newObserver)
{
	AddObserver(t_newObserver);
}

void BulletHolder::update()
{
	for (auto i : m_bullets)
	{
		i.update();
	}
}

void BulletHolder::spawnNewBullet(sf::Vector2f t_loc, sf::Vector2f t_target)
{
	bool spawned = false;
	float bulletSpeed = 1000.f;

	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		if (!m_bullets.at(i).m_active)
		{
			spawned = true;

			m_bullets.at(i).m_bullet = std::make_shared<sf::CircleShape>();
			m_bullets.at(i).m_bullet->setPosition(t_loc);
			m_bullets.at(i).m_bullet->setRadius(5.f);
			m_bullets.at(i).m_bullet->setFillColor(sf::Color::Green);
			m_bullets.at(i).m_bullet->setOrigin(sf::Vector2f(m_bullets.at(i).m_bullet->getGlobalBounds().width / 2.f, m_bullets.at(i).m_bullet->getGlobalBounds().height / 2.f));
			RenderObject::getInstance().add(m_bullets.at(i).m_bullet);

			m_bullets.at(i).m_active = true;

			m_bullets.at(i).m_displacement = math::displacement(t_loc, t_target);
			m_bullets.at(i).m_displacement *= bulletSpeed;
		}
	}
	if (!spawned)
	{
		Bullet newBullet;

		newBullet.m_bullet = std::make_shared<sf::CircleShape>();
		newBullet.m_bullet->setPosition(t_loc);
		newBullet.m_bullet->setRadius(5.f);
		newBullet.m_bullet->setFillColor(sf::Color::Green);
		newBullet.m_bullet->setOrigin(sf::Vector2f(newBullet.m_bullet->getGlobalBounds().width / 2.f, newBullet.m_bullet->getGlobalBounds().height / 2.f));
		RenderObject::getInstance().add(newBullet.m_bullet);

		newBullet.m_active = true;

		newBullet.m_displacement = math::displacement(t_loc, t_target);
		newBullet.m_displacement *= bulletSpeed;


		m_bullets.push_back(newBullet);
	}
}

void BulletHolder::checkCollisions(sf::FloatRect t_bounds)
{
	for (auto i : m_bullets)
	{
		if(i.m_active)
		{
			if (i.m_bullet->getGlobalBounds().intersects(t_bounds))
			{
				collisionInfo info;
				info.collidingBullet = i;
				info.collidedNPC = t_bounds;
				notifyAll(info);
				i.m_active = false;
				i.m_bullet->setPosition(-500000.f, -5000000.f);
			}
		}
	}
}

void BulletHolder::checkWallCollision(int t_roomNum)
{
	for (auto i : m_bullets)
	{
		if (i.m_active)
		{
			sf::RectangleShape body;
			body.setSize(sf::Vector2f(i.m_bullet->getGlobalBounds().width, i.m_bullet->getGlobalBounds().width));
			body.setPosition(i.m_bullet->getPosition());
			if (RoomPlan::getInstance().collides(body, t_roomNum))
			{
				i.m_active = false;
				i.m_bullet->setPosition(-500000.f, -5000000.f);
			}
		}
	}
}

void Bullet::update()
{
	if(m_active)
		m_bullet->move(m_displacement * Game::deltaTime);
}
