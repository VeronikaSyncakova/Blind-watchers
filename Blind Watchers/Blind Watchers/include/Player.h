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
};
