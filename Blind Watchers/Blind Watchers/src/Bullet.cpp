#include "Bullet.h"
#include "Game.h"
#include "RenderObject.h"

sf::Vector2f displacement(sf::Vector2f t_loaction, sf::Vector2f t_aim)
{
	sf::Vector2f displacement = t_aim - t_loaction;
	displacement /= std::sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
	return displacement;
}

BulletHolder::BulletHolder()
{
}

BulletHolder::~BulletHolder()
{
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

			m_bullets.at(i).m_displacement = displacement(t_loc, t_target);
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

		newBullet.m_displacement = displacement(t_loc, t_target);
		newBullet.m_displacement *= bulletSpeed;


		m_bullets.push_back(newBullet);
	}
}

void Bullet::update()
{
	m_bullet->move(m_displacement * Game::deltaTime);
}
