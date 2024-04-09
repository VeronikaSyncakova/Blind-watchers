#pragma once

#include <SFML/Graphics.hpp>

class Pawn
{
public:
	Pawn();
	~Pawn();

	virtual void initialise() = 0;
	virtual void update() = 0;
private:

protected:
	sf::Vector2f m_position;
};