#pragma once

#include <SFML/Graphics.hpp>

class visionCone
{
public:
	visionCone(sf::Vector2f t_spawnPos, float t_len, float t_angle);
	void moveCone(sf::Vector2f t_newPosition);
private:
	std::shared_ptr<sf::ConvexShape> m_cone;
};