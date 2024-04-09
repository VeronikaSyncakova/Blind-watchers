#pragma once

#include "Pawn.h"

class Player : public Pawn
{
public:
	Player();
	~Player();

	void initialise()override;
	void update()override;

private:
	std::shared_ptr<sf::RectangleShape> m_body;
	float m_moveSpeed{ 0.f };
};
