#include "Player.h"
#include "playerStats.h"
#include "CharacterSelection.h"
#include "RenderObject.h"
#include "Game.h"

Player::Player()
{
	m_body = std::make_shared<sf::RectangleShape>();
	
	m_active = true;

	PlayerData tempData;
	tempData = Game::s_selectedPlayer;
	m_position = { 100.f,100.f };
	m_body->setPosition(m_position);
	m_body->setSize(tempData.m_size);
	m_body->setOrigin(tempData.m_size / 2.f);
	m_body->setFillColor(tempData.m_color);
	m_moveSpeed = tempData.m_speed;
	m_sprintSpeed = tempData.m_sprintSpeed;
	m_maxSprintTime = tempData.m_sprintTime;
	m_sprintTimeLeft = m_maxSprintTime;

	RenderObject::getInstance().add(m_body);

	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);
}

Player::~Player()
{
}

void Player::update()
{
	if (m_sprinting)
	{
		m_sprintTimeLeft -= Game::deltaTime;

		if (m_sprintTimeLeft < 0.f)
			m_sprintTimeLeft = 0.f;
	}
	else
	{
		m_sprintTimeLeft += Game::deltaTime;
		if (m_sprintTimeLeft > m_maxSprintTime)
		{
			m_sprintTimeLeft = m_maxSprintTime;
		}
	}
}

void Player::moveBody(sf::Vector2f const& t_moveVector)
{
	float ExtraSpeed = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		m_sprinting = true;
		if(m_sprintTimeLeft > 0.f)
			ExtraSpeed = m_sprintSpeed;
	}
	else
	{
		m_sprinting = false;
	}
	
	//collision with room walls and doors
	if (RoomPlan::getInstance().collides(*m_body, m_roomNumber) && !RoomPlan::getInstance().usesDoor(*m_body, m_roomNumber))
	{//collision with walls 
		sf::Vector2f deflectVector = RoomPlan::getInstance().deflectVector(*m_body, m_roomNumber);
		m_body->move( deflectVector* ((m_moveSpeed + ExtraSpeed) * Game::deltaTime));
		RenderObject::getInstance().updateCamera(deflectVector);
	}
	else
	{
		m_body->move(t_moveVector * ((m_moveSpeed + ExtraSpeed) * Game::deltaTime));
		RenderObject::getInstance().updateCamera(t_moveVector);
		if (RoomPlan::getInstance().usesDoor(*m_body, m_roomNumber)) //using doors
			m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_body->getPosition()); //update room number
	}

	m_position = m_body->getPosition();
}

void Player::position(sf::Vector2f& t_position)
{
	m_position = t_position;
	m_body->setPosition(m_position);
	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);
}
