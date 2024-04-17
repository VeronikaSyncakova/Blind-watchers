#include "States.h"
#include "Game.h"
#include "Pawn.h"
#include "blindNpc.h"
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

/// <summary>
/// takes the input from the player and moves the pawn by that amount
/// </summary>
/// <param name="t_pawn"></param>
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

/// <summary>
/// changes the current used command based on the new "state" that is passed in
/// </summary>
/// <param name="t_newState"></param>
/// <param name="t_pawn"></param>
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
	case State::Patrol:
		t_pawn->m_state = std::make_shared<PatrolState>();
		t_pawn->m_state->enter(t_pawn);
		break;
	default:
		t_pawn->m_state = std::make_shared<NoneState>();
		t_pawn->m_state->enter(t_pawn);
		break;
	}
}

// call the update function on the current state
void StateManager::update(std::shared_ptr<Pawn> t_pawn)
{
	t_pawn->m_state->update(t_pawn);
}

// set the start position on which the circle will be based
void WanderState::enter(std::shared_ptr<Pawn> t_pawn)
{
	m_startPosition = t_pawn->getPosition();
}

/// <summary>
/// move the character randomly within the radius that is given
/// </summary>
/// <param name="t_pawn"></param>
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
				if (pos.x > m_startPosition.x)
				{
					m_chosenDirection.x = -1.f;
				}
				if (pos.x < m_startPosition.x)
				{
					m_chosenDirection.x = 1.f;
				}
				if (pos.y > m_startPosition.y)
				{
					m_chosenDirection.y = -1.f;
				}
				if (pos.y < m_startPosition.y)
				{
					m_chosenDirection.y = 1.f;
				}
			}
			else
			{
				m_chosenDirection = sf::Vector2f(static_cast<float>((rand() % 3) - 1), static_cast<float>((rand() % 3) - 1));
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

void PatrolState::enter(std::shared_ptr<Pawn> t_pawn)
{
}

/// <summary>
/// move the npc along the patrol path given by the points that the npc stores
/// </summary>
/// <param name="t_pawn"></param>
void PatrolState::update(std::shared_ptr<Pawn> t_pawn)
{
	sf::Vector2f pos = t_pawn->getPosition();
	if (math::circleIntersects(t_pawn->getPosition(), t_pawn->getPatrolPoints().at(m_nextPoint), 1.f, 1.f))
	{
		m_nextPoint++;
		if (m_nextPoint >= static_cast<int>(t_pawn->getPatrolPoints().size()))
			m_nextPoint = 0;
	}
	sf::Vector2f nextPoint = t_pawn->getPatrolPoints().at(m_nextPoint);
	sf::Vector2f chosenPath = { 0.f,0.f };
	chosenPath = math::displacement(pos, nextPoint);
	t_pawn->moveBody(chosenPath);
}

void PatrolState::exit(std::shared_ptr<Pawn> t_pawn)
{
}

void PatrolState::skipPoint(std::shared_ptr<Pawn> t_pawn)
{
	m_nextPoint++;
	if (m_nextPoint >= static_cast<int>(t_pawn->getPatrolPoints().size()))
		m_nextPoint = 0;
}

void SeekPlayer::enter(std::shared_ptr<Pawn> t_pawn)
{
}

void SeekPlayer::update(std::shared_ptr<Pawn> t_pawn)
{
	sf::Vector2f displacement = math::displacement(t_pawn->getPosition(), m_playerPos);
	t_pawn->moveBody(displacement);
	t_pawn->rotate(math::displacementToDegrees(displacement));
}

void SeekPlayer::exit(std::shared_ptr<Pawn> t_pawn)
{
}

void SeekPlayer::SetPlayer(sf::Vector2f t_playerPos)
{
	m_playerPos = t_playerPos;
}
