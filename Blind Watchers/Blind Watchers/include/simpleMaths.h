#ifndef SIMPLE_MATHS_H
#define SIMPLE_MATHS_H

#include <SFML/Graphics.hpp>

namespace math
{
	float distancebetweenPoints(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return ((t_pos2.x - t_pos2.x) * (t_pos2.x - t_pos2.x) + (t_pos2.y - t_pos2.y) * (t_pos2.y - t_pos2.y));
	}

	bool circleIntersects(sf::Vector2f t_pos1, sf::Vector2f t_pos2, float t_radius1, float t_radius2)
	{
		return (distancebetweenPoints(t_pos1, t_pos2) <= (t_radius1 + t_radius2) * (t_radius1 + t_radius2));
	}
}

#endif // !SIMPLE_MATHS_H
