#include "Door.h"

Door::Door()
{
}

void Door::init(DoorData& data, sf::Texture& t_texture)
{
	m_position = sf::Vector2f(data.m_positionX, data.m_positionY);
	m_rotation = data.m_rotation;
	if (data.m_doorType == "West")
	{
		m_type = DoorPosition::West;
	}
	else if (data.m_doorType == "East")
	{
		m_type = DoorPosition::East;
	}
	else if (data.m_doorType == "North")
	{
		m_type = DoorPosition::North;
	}
	else if (data.m_doorType == "South")
	{
		m_type = DoorPosition::South;
	}
	m_body = std::make_shared<sf::RectangleShape>();
	m_body->setSize(m_size);
	m_body->setFillColor(sf::Color::Green);
	m_body->setOrigin(m_size / 2.f);
	m_body->setPosition(m_position);
	m_body->setRotation(m_rotation);
	//RenderObject::getInstance().add(m_body);

	m_sprite = std::make_shared<sf::Sprite>();
	m_sprite->setTexture(t_texture);
	m_sprite->setOrigin(m_body->getOrigin());
	m_sprite->setPosition(m_position);
	m_sprite->setRotation(m_rotation);
	RenderObject::getInstance().add(m_sprite);
}

sf::Vector2f Door::getPosition()
{
	return m_position;
}

bool Door::collides(sf::RectangleShape& t_object)
{
	if (m_body->getGlobalBounds().intersects(t_object.getGlobalBounds()))
		return true;
	return false;
}
