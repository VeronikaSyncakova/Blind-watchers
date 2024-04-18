#include "Player.h"
#include "playerStats.h"
#include "CharacterSelection.h"
#include "RenderObject.h"
#include "Game.h"

Player::Player()
{
	m_followCam.setCameraType(CameraTracker::CameraType::Delayed_Follow);

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

	//RenderObject::getInstance().add(m_body);

	if (!m_bodyTexture.loadFromFile("ASSETS\\IMAGES\\Misc\\"+tempData.m_name+".png"))
		DEBUG_MSG("COULDNT LOAD PLAYER");


	m_bodySprite = std::make_shared<AnimatedSprite>(0.2f, m_bodyTexture);
	sf::Vector2f size = sf::Vector2f(m_bodyTexture.getSize().x, m_bodyTexture.getSize().y);
	size.x = size.x / 3.f;//amount of frames
	m_bodySprite->setOrigin(size/2.f);

	m_bodySprite->addFrame(sf::IntRect(0,0,35,35));
	m_bodySprite->addFrame(sf::IntRect(35, 0, 35, 35));
	m_bodySprite->addFrame(sf::IntRect(0, 0, 35, 35));
	m_bodySprite->addFrame(sf::IntRect(70, 0, 35, 35));

	m_bodySprite->setPosition(m_position);

	RenderObject::getInstance().add(m_bodySprite);

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

void Player::expire()
{
	DEBUG_MSG("DEAD");
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
		//RenderObject::getInstance().updateCamera(deflectVector * ((m_moveSpeed + ExtraSpeed) * Game::deltaTime));
	}
	else
	{
		m_body->move(t_moveVector * ((m_moveSpeed + ExtraSpeed) * Game::deltaTime));
		//RenderObject::getInstance().updateCamera(t_moveVector * ((m_moveSpeed + ExtraSpeed) * Game::deltaTime));
		if (RoomPlan::getInstance().usesDoor(*m_body, m_roomNumber)) //using doors
			m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_body->getPosition()); //update room number
	}
	if(t_moveVector.x != 0.f || t_moveVector.y != 0.f)
		m_bodySprite->update();
	m_position = m_body->getPosition();
	m_followCam.update(m_position);
	m_bodySprite->setPosition(m_position);
}

void Player::rotate(float t_angle)
{
	m_bodySprite->setRotation(t_angle);
}

void Player::position(sf::Vector2f& t_position)
{
	m_position = t_position;
	m_body->setPosition(m_position);
	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);
	m_bodySprite->setPosition(m_position);
}

void Player::writeYAML(YAML::Emitter& t_out)
{
}
