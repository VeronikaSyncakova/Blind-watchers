#pragma once

#include <SFML/Graphics.hpp>

struct Bullet
{
	void update();

	std::shared_ptr<sf::CircleShape> m_bullet;
	sf::Vector2f m_displacement;
	bool m_active;
};

class BulletHolder
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
