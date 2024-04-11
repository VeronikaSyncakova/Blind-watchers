#include "States.h"
#include "Game.h"
#include "Pawn.h"
#include "simpleMaths.h"

void NoneState::enter(std::shared_ptr<Pawn> t_pawn)
{
}

void NoneState::update(std::shared_ptr<Pawn> t_pawn)
{
}

void NoneState::exit(std::shared_ptr<Pawn> t_pawn)
{
}


void playerInputState::enter(std::shared_ptr<Pawn> t_pawn)
{
}

void playerInputState::update(std::shared_ptr<Pawn> t_pawn)
{
	sf::Vector2f moveVector{ 0.f,0.f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveVector.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveVector.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveVector.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveVector.x -= 1;
	}
	t_pawn->moveBody(moveVector);
}

void playerInputState::exit(std::shared_ptr<Pawn> t_pawn)
{
}

void StateManager::changeCommand(State t_newState, std::shared_ptr<Pawn> t_pawn)
{
	if (t_pawn->m_state != nullptr)
		t_pawn->m_state->exit(t_pawn);

	t_pawn->m_currentState = t_newState;

	switch (t_pawn->m_currentState)
	{
	case State::None:
		t_pawn->m_state = std::make_shared<NoneState>();
		t_pawn->m_state->enter(t_pawn);
		break;
	case State::PlayerInput:
		t_pawn->m_state = std::make_shared<playerInputState>();
		t_pawn->m_state->enter(t_pawn);
		break;
	case State::Wander:
		t_pawn->m_state = std::make_shared<WanderState>();
		t_pawn->m_state->enter(t_pawn);
		break;
	default:
		t_pawn->m_state = std::make_shared<NoneState>();
		t_pawn->m_state->enter(t_pawn);
		break;
	}
}

void StateManager::update(std::shared_ptr<Pawn> t_pawn)
{
	t_pawn->m_state->update(t_pawn);
}

void WanderState::enter(std::shared_ptr<Pawn> t_pawn)
{
	m_startPosition = t_pawn->getPosition();
}

void WanderState::update(std::shared_ptr<Pawn> t_pawn)
{
	if (m_wanderWait <= 0.f)
	{
		if (m_wanderTimeLeft <= 0.f)
		{
			m_wanderWait = 1.f;
			m_wanderTimeLeft = static_cast<float>(rand() / float(RAND_MAX) * 2.f);

			sf::Vector2f pos = t_pawn->getPosition();

			if (!math::circleIntersects(m_startPosition, pos, m_wanderRadius, 1.f))
			{
				
			}
			else
			{
				m_chosenDirection = sf::Vector2f((rand() % 3) - 1, (rand() % 3) - 1);
			}
		}
		m_wanderTimeLeft -= Game::deltaTime;
		t_pawn->moveBody(m_chosenDirection);
	}
	else
	{
		m_wanderWait -= Game::deltaTime;
	}
}

void WanderState::exit(std::shared_ptr<Pawn> t_pawn)
{
}
