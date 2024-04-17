#include "Room.h"

Room::Room()
{
}

void Room::init(RoomData& data)
{
	m_roomSize = sf::Vector2f(data.m_sizeX, data.m_sizeY);
	m_position = sf::Vector2f(data.m_positionX, data.m_positionY);
	if (data.m_roomType == "TopRight")
	{
		m_roomType = RoomType::TopRight;
		//m_roomWalls->setFillColor(sf::Color::Red);
	}
	else if (data.m_roomType == "TopLeft")
	{
		m_roomType = RoomType::TopLeft;
		//m_roomWalls->setFillColor(sf::Color::Blue);
	}
	else if (data.m_roomType == "BottomRight")
	{
		m_roomType = RoomType::BottomRight;
		//m_roomWalls->setFillColor(sf::Color::Green);
	}
	else if (data.m_roomType == "BottomLeft")
	{
		m_roomType = RoomType::BottomLeft;
		//m_roomWalls->setFillColor(sf::Color::Magenta);
	}

	m_roomWalls = std::make_shared<sf::RectangleShape>();
	m_roomWalls->setSize(m_roomSize);
	m_roomWalls->setFillColor(sf::Color::Transparent);
	m_roomWalls->setOutlineThickness(4.f);
	m_roomWalls->setOutlineColor(sf::Color::White);
	m_roomWalls->setPosition(m_position);
	RenderObject::getInstance().add(m_roomWalls);
}

bool Room::inside(sf::Vector2f t_position)
{
	if (m_position.x <= t_position.x && m_position.x + m_roomSize.x >= t_position.x &&
		m_position.y <= t_position.y && m_position.y + m_roomSize.y >= t_position.y)
		return true;
	return false;
}

bool Room::checkCollision(sf::RectangleShape& t_object)
{
	sf::Vector2f pos = t_object.getPosition();
	sf::Vector2f size = t_object.getSize()/2.f;
	if (m_position.x >= pos.x-size.x || m_position.x + m_roomSize.x <= pos.x + size.x ||
		m_position.y >= pos.y-size.x || m_position.y + m_roomSize.y <= pos.y + size.y)
		return true;
	return false;
}

sf::Vector2f Room::deflectVector(sf::RectangleShape& t_object)
{
	sf::Vector2f pos = t_object.getPosition();
	sf::Vector2f size = t_object.getSize()/2.f;
	if (m_position.x >= pos.x-size.x)//left
	{
		return sf::Vector2f(1.f,0.f);
	}
	else if (m_position.x + m_roomSize.x <= pos.x + size.x)//right
	{
		return sf::Vector2f(-1.f, 0.f);
	}
	else if (m_position.y >= pos.y-size.y)//up
	{
		return sf::Vector2f(0.f, 1.f);
	}
	else if (m_position.y + m_roomSize.y <= pos.y + size.y)//down
	{
		return sf::Vector2f(0.f, -1.f);
	}
}

void Room::changeHighlite(sf::Color t_color)
{
	m_roomWalls->setOutlineColor(t_color);
}

void Room::changeColor(sf::Color t_color)
{
	m_roomWalls->setFillColor(t_color);
}

sf::Vector2f Room::getCenter()
{
	return sf::Vector2f(m_position.x+(m_roomSize.x/2.f), m_position.y+(m_roomSize.y/2.f));
}

sf::Vector2f Room::getPosition()
{
	return m_position;
}
