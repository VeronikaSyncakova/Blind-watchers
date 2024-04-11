#include "blindNpc.h"
#include "RenderObject.h"

blindNpc::blindNpc(npcData& t_characterData)
{
	m_body = std::make_shared<body>();
	m_body->initialiseBody(t_characterData);
}

blindNpc::~blindNpc()
{
}

void blindNpc::update()
{
}

void blindNpc::moveBody(sf::Vector2f const& t_moveVector)
{
	m_body->moveBody(t_moveVector * m_maxSpeed);
}

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
