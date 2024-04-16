#include "VisionCone.h"
#include "simpleMaths.h"
#include "RenderObject.h"

visionCone::visionCone(sf::Vector2f t_spawnPos, float t_len, float t_angle)
{
	m_cone = std::make_shared<sf::ConvexShape>(3);

	float useAngle = t_angle / 2.f;
	m_cone->setPoint(0, sf::Vector2f(0.f,0.f));
	sf::Vector2f nextPoint = math::angleToPosition(t_len, useAngle);
	m_cone->setPoint(1, nextPoint);
	nextPoint = math::angleToPosition(t_len, -useAngle);
	m_cone->setPoint(2, nextPoint);
	//nextPoint = math::angleToPosition(t_len, -useAngle);
	//m_cone->setPoint(3, nextPoint);
	//nextPoint = math::angleToPosition(t_len, -useAngle * 2);
	//m_cone->setPoint(4, nextPoint);

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
