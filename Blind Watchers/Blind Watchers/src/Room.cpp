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
