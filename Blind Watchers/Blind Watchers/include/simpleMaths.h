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
	static float displacementToDegrees(sf::Vector2f t_displacement)
	{
		float angle = radiansToDegrees(std::atan2f(t_displacement.y, t_displacement.x));
		if (angle < 0.f)
			angle = 360.f + angle;
		if (angle > 360.f)
		{
			angle = angle - 360.f;
		}
		return angle;
	}
	static bool checkIsLeft(sf::Vector2f t_pointA, sf::Vector2f t_pointB, sf::Vector2f t_checkPoint)
	{
		// return ((x2 - x1) * (y3 - y1)) - ((y2 - y1) * (x3 - x1))
		return ( ( (t_pointB.x - t_pointA.x) * (t_checkPoint.y - t_pointA.y) - (t_pointB.y - t_pointA.y) * (t_checkPoint.x - t_pointA.x) ) > 0 );
	}
	static bool containedInCone(sf::Vector2f t_pointA, sf::Vector2f t_pointB, sf::Vector2f t_pointC, sf::Vector2f t_checkPoint)
	{
		if (circleIntersects(t_pointA, t_checkPoint, distancebetweenPoints(t_pointA, t_pointB), 1.f))
			if (checkIsLeft(t_pointA, t_pointB, t_checkPoint) && checkIsLeft(t_pointC, t_pointA, t_checkPoint))
				return true;
		return false;
	}
	static sf::Vector2f rotatePoint(sf::Vector2f t_point, float t_angle)
	{
		float cos = std::cos(-t_angle);
		float sin = std::sin(-t_angle);
		float x = t_point.x * cos - t_point.y * sin;
		float y = t_point.x * sin + t_point.y * cos;
		return sf::Vector2f(x, y);
	}
	static bool coneIntersectsBox(sf::ConvexShape t_cone, sf::FloatRect t_box)
	{
		bool intersects = false;
		sf::Vector2f coneMid = t_cone.getPoint(0) + t_cone.getPosition();
		sf::Vector2f coneStart = t_cone.getPoint(1) + t_cone.getPosition();
		sf::Vector2f coneEnd = t_cone.getPoint(t_cone.getPointCount() - 1) + t_cone.getPosition();
		
		coneStart = (rotatePoint(t_cone.getPoint(1), t_cone.getRotation()) + t_cone.getPosition());
		coneEnd = (rotatePoint(t_cone.getPoint(t_cone.getPointCount() - 1), t_cone.getRotation())) + t_cone.getPosition();

		if (containedInCone(coneMid, coneStart, coneEnd, t_box.getPosition()))
			intersects = true;
		else if (containedInCone(coneMid, coneStart, coneEnd, t_box.getPosition() + t_box.getSize()))
			intersects = true;
		else if (containedInCone(coneMid, coneStart, coneEnd, t_box.getPosition() + sf::Vector2f(t_box.getSize().x, 0.f)))
			intersects = true;
		else if (containedInCone(coneMid, coneStart, coneEnd, t_box.getPosition() + sf::Vector2f(0.f, t_box.getSize().y)))
			intersects = true;

		return intersects;
	}
};

#endif // !SIMPLE_MATHS_H
