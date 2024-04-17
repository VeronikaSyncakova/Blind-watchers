#include "VisionCone.h"
#include "simpleMaths.h"
#include "RenderObject.h"

visionCone::visionCone(sf::Vector2f t_spawnPos, float t_len, float t_angle)
{
	int divides = 8;
	m_cone = std::make_shared<sf::ConvexShape>(divides);

	int pointAmt = divides - 1;
	float useAngle = t_angle / pointAmt;
	m_cone->setPoint(0, sf::Vector2f(0.f,0.f));

	int half = pointAmt / 2.f;
	sf::Vector2f nextPoint;
	for (int i = 0; i < pointAmt; i++)
	{
		nextPoint = math::angleToPosition(t_len, useAngle * (i - half));
		m_cone->setPoint(i, nextPoint);
	}

	m_cone->setFillColor(sf::Color::Transparent);
	m_cone->setOutlineColor(sf::Color::White);
	m_cone->setOutlineThickness(1.f);

	m_cone->setPosition(t_spawnPos);

	RenderObject::getInstance().add(m_cone);
}



void visionCone::moveCone(sf::Vector2f t_newPosition)
{
	m_cone->setPosition(t_newPosition);
}

void visionCone::setRotation(float t_angle)
{
	m_cone->setRotation(t_angle);
}

bool visionCone::checkCollision(sf::FloatRect t_playerBounds)
{
	if (math::coneIntersectsBox(*m_cone, t_playerBounds))
	{
		DEBUG_MSG("COLLIDING");
		return true;
	}
	return false;
}
