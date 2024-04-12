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
}

blindNpc::~blindNpc()
{
}

void blindNpc::update()
{
}

void blindNpc::moveBody(sf::Vector2f const& t_moveVector)
{
	m_position += t_moveVector * m_maxSpeed * Game::deltaTime;
	m_body->moveBody(m_position);
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

	RenderObject::getInstance().add(m_rectangle);
}

void body::moveBody(sf::Vector2f const& t_newPos)
{
	m_rectangle->setPosition(t_newPos);
}
