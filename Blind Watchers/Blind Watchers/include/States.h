#pragma once

#include "AbstractState.h"
#include <SFML/Graphics.hpp>

enum class State
{
	None, PlayerInput, Wander
};

class NoneState : public AbstractState
{
public:
	virtual void enter(std::shared_ptr<Pawn> t_pawn);
	virtual void update(std::shared_ptr<Pawn> t_pawn);
	virtual void exit(std::shared_ptr<Pawn> t_pawn);
};

class playerInputState : public AbstractState
{
public:
	virtual void enter(std::shared_ptr<Pawn> t_pawn);
	virtual void update(std::shared_ptr<Pawn> t_pawn);
	virtual void exit(std::shared_ptr<Pawn> t_pawn);
};

class WanderState : public AbstractState
{
public:
	virtual void enter(std::shared_ptr<Pawn> t_pawn);
	virtual void update(std::shared_ptr<Pawn> t_pawn);
	virtual void exit(std::shared_ptr<Pawn> t_pawn);
private:
	float m_wanderRadius{ 100.f };
	sf::Vector2f m_startPosition;

	float m_wanderTimeLeft{ -1.f };
	float m_wanderWait{ 1.f };

	sf::Vector2f m_chosenDirection{ 0.f,0.f };
};

class StateManager
{
public:
	static void changeCommand(State t_newState, std::shared_ptr<Pawn> t_pawn);
	static void update(std::shared_ptr<Pawn> t_pawn);
};

