#pragma once

#include <SFML/Graphics.hpp>
#include "States.h"

class Pawn
{
friend StateManager;
public:
	Pawn();
	~Pawn();

	virtual void initialise() = 0;
	virtual void update() = 0;

	// normalised vector that the pawn will move along
	virtual void moveBody(sf::Vector2f const& t_moveVector) = 0;
private:

protected:
	sf::Vector2f m_position;
	float m_moveSpeed{ 0.f };

	State m_currentState{ State::None };
	std::shared_ptr<AbstractState> m_state;
};