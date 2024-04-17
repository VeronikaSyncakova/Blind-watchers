#ifndef SIMPLE_MATHS_H
#define SIMPLE_MATHS_H

#include <SFML/Graphics.hpp>
#include "DEBUG.h"

#define PI 3.1415926535897932384626433f

class math
{
public:
	static float distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return std::sqrt((t_pos1.x - t_pos2.x) * (t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y) * (t_pos1.y - t_pos2.y));
	}
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
	static float degreesToRadians(float t_degrees)
	{
		float radians = t_degrees * (PI / 180.0f);
		return radians;
	}
	static float radiansToDegrees(float t_radians)
	{
		float degrees = t_radians * 180.f / PI;
		return degrees;
	}
	static sf::Vector2f angleToPosition(float t_hypLen, float t_angle)
	{
		sf::Vector2f position;
		t_angle = degreesToRadians(t_angle);
		position.x = std::cos(t_angle) * t_hypLen;
		position.y = std::sin(t_angle) * t_hypLen;
		return position;
	}
};

#endif // !SIMPLE_MATHS_H
