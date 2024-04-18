#include "WalkingStick.h"
#include "RenderObject.h"
#include "Game.h"

WalkingStick::WalkingStick()
{
}

WalkingStick::~WalkingStick()
{
}

void WalkingStick::initialise(sf::Vector2f t_pos, float t_startAngle)
{
	m_stick = std::make_shared<sf::RectangleShape>(sf::Vector2f(80.f, 4.f));
	
	m_setAngle = t_startAngle;
	m_stick->setOrigin(0.f, 2.f);
	m_stick->setRotation(t_startAngle);
	m_stick->setFillColor(sf::Color::Black);
	m_stick->setPosition(t_pos);

	RenderObject::getInstance().addParticles(m_stick);
}

void WalkingStick::rotate(float t_newRotation)
{
	m_setAngle = t_newRotation;
}

void WalkingStick::setPos(sf::Vector2f t_newPos)
{
	m_stick->setPosition(t_newPos);
}

void WalkingStick::update()
{
	if (m_positive)
	{
		m_targetAngle = (m_targetAngle + m_rotateSpeed * Game::deltaTime);

		if (m_targetAngle >= 25.f)
		{
			m_positive = false;
		}
	}
	else
	{
		m_targetAngle = (m_targetAngle - m_rotateSpeed * Game::deltaTime);
		if (m_targetAngle <= -25.f)
		{
			m_positive = true;
		}
	}
	m_stick->setRotation(m_setAngle + m_targetAngle);
}
