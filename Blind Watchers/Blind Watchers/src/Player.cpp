#include "Player.h"
#include "playerStats.h"
#include "CharacterSelection.h"
#include "RenderObject.h"
#include "Game.h"

Player::Player()
{
	m_body = std::make_shared<sf::RectangleShape>();
	
	PlayerData tempData;
	tempData = Game::s_selectedPlayer;
	m_body->setPosition(100.f,100.f);
	m_body->setSize(tempData.m_size);
	m_body->setFillColor(tempData.m_color);
	m_moveSpeed = tempData.m_speed;

	RenderObject::getInstance().add(m_body);
}

Player::~Player()
{
}

void Player::initialise()
{
}

void Player::update()
{
}

void Player::moveBody(sf::Vector2f const& t_moveVector)
{
	m_body->move(t_moveVector * (m_moveSpeed * Game::deltaTime));
}
