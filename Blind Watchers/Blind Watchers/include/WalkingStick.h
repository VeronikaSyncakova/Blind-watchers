#pragma once

#include <SFML/Graphics.hpp>

class WalkingStick
{
public:
	WalkingStick();
	~WalkingStick();

	void initialise(sf::Vector2f t_pos, float t_startAngle = 0.f);
	void rotate(float t_newRotation);
	void setPos(sf::Vector2f t_newPos);
	void update();

private:
	std::shared_ptr<sf::RectangleShape> m_stick;
	float m_rotateSpeed{ 100.f };
	bool m_positive{ false };
	float m_setAngle{ 0.f };
	float m_targetAngle{ 0.f };
};