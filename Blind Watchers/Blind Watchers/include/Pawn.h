#pragma once

#include <SFML/Graphics.hpp>
#include "States.h"

class Pawn
{
friend StateManager;
public:
	Pawn();
	~Pawn();

	virtual void update() = 0;

	// normalised vector that the pawn will move along
	virtual void moveBody(sf::Vector2f const& t_moveVector) = 0;

	bool getActive() { return m_active; }
	virtual sf::FloatRect getBounds() = 0;
	sf::Vector2f getPosition() { return m_position; }
	std::vector<sf::Vector2f> getPatrolPoints() { return m_patrolPoints; }
private:

protected:
	sf::Vector2f m_position;
	float m_moveSpeed{ 0.f };

	State m_currentState{ State::None };
	std::shared_ptr<AbstractState> m_state;

	bool m_active{ false };
	std::vector<sf::Vector2f> m_patrolPoints;
};