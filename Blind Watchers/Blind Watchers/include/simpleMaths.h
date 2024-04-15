#ifndef SIMPLE_MATHS_H
#define SIMPLE_MATHS_H

#include <SFML/Graphics.hpp>

class math
{
public:
	static float distancebetweenPoints(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return ((t_pos2.x - t_pos1.x) * (t_pos2.x - t_pos1.x) + (t_pos2.y - t_pos1.y) * (t_pos2.y - t_pos1.y));
	}

	static bool circleIntersects(sf::Vector2f t_pos1, sf::Vector2f t_pos2, float t_radius1, float t_radius2)
	{
		float distBetweenPoints = distancebetweenPoints(t_pos1, t_pos2);
		float radSize = (t_radius1 + t_radius2) * (t_radius1 + t_radius2);
		return (distBetweenPoints <= radSize);
	}

	static sf::Vector2f displacement(sf::Vector2f t_loaction, sf::Vector2f t_aim)
	{
		sf::Vector2f displacement = t_aim - t_loaction;
		displacement /= std::sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
		return displacement;
	}
};

#endif // !SIMPLE_MATHS_H
