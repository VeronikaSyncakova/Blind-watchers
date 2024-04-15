#include "blindNpc.h"
#include "RenderObject.h"
#include "Game.h"

/// <summary>
/// setup the shared pointer for the body
/// </summary>
/// <param name="t_characterData"></param>
blindNpc::blindNpc(npcData& t_characterData)
{
	m_body = std::make_shared<body>();
	m_body->initialiseBody(t_characterData);
	m_position = t_characterData.position;

	setPatrolPoints(t_characterData);
	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);
}

blindNpc::~blindNpc()
{
}

void blindNpc::update()
{
}

void blindNpc::moveBody(sf::Vector2f const& t_moveVector)
{
	if (RoomPlan::getInstance().collides(m_body->getBody(), m_roomNumber))
	{
		sf::Vector2f deflection = RoomPlan::getInstance().deflectVector(m_body->getBody(), m_roomNumber);
		m_position += deflection * m_maxSpeed * Game::deltaTime;
		if (auto t = std::dynamic_pointer_cast<PatrolState>(m_state))
		{
			t->skipPoint(std::make_shared<blindNpc>(*this));
		}
	}
	else
	{
		m_position += t_moveVector * m_maxSpeed * Game::deltaTime;
	}
	m_body->moveBody(m_position);
}

npcData blindNpc::getData()
{
	npcData currentData;
	currentData.position = m_body->getBody().getPosition();
	currentData.color = m_body->getBody().getFillColor();
	currentData.size = m_body->getBody().getSize();
	currentData.speed = m_moveSpeed;
	currentData.patrolPoints = m_patrolPoints;
	return currentData;
}

void blindNpc::position(sf::Vector2f& t_position)
{
	m_position = t_position;
	m_body->m_rectangle->setPosition(m_position);
	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);
}

void blindNpc::setPatrolPoints(npcData& t_characterData)
{
	m_patrolPoints = t_characterData.patrolPoints;
}

/// <summary>
/// read the data from the npcData struct and set the rectangles properties based on that
/// </summary>
/// <param name="t_data"></param>
void body::initialiseBody(npcData& t_data)
{
	m_rectangle = std::make_shared<sf::RectangleShape>();

	sf::Color bodyColor = t_data.color;
	m_rectangle->setFillColor(bodyColor);

	m_rectangle->setPosition(t_data.position);

	m_rectangle->setSize(t_data.size);
	m_rectangle->setOrigin(t_data.size / 2.f);

	RenderObject::getInstance().add(m_rectangle);
}

void body::moveBody(sf::Vector2f const& t_newPos)
{
	m_rectangle->setPosition(t_newPos);
}

sf::RectangleShape body::getBody()
{
	return *m_rectangle;
}
