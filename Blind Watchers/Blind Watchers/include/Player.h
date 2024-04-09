#pragma once

#include "Pawn.h"

class Player : public Pawn
{
public:
	Player();
	~Player();

	void initialise()override;
	void update()override;

	void moveBody(sf::Vector2f const& t_moveVector)override;
private:
	std::shared_ptr<sf::RectangleShape> m_body;

	bool m_sprinting{ false };
	float m_sprintTimeLeft{ 2.f };
	float m_maxSprintTime{ 2.f };
	float m_sprintSpeed{ 200.f };
};
