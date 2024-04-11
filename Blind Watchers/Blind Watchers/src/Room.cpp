#include "Room.h"

Room::Room(RoomData& data)
{
	m_roomSize = sf::Vector2f(data.m_sizeX, data.m_sizeY);
	m_position = sf::Vector2f(data.m_positionX, data.m_positionY);
	if (data.m_roomType == "TopRight")
	{
		m_roomType = RoomType::TopRight;
	}
	else if (data.m_roomType == "TopLeft")
	{
		m_roomType = RoomType::TopLeft;
	}
	else if (data.m_roomType == "BottomRight")
	{
		m_roomType = RoomType::BottomRight;
	}
	else if (data.m_roomType == "BottomLeft")
	{
		m_roomType = RoomType::BottomLeft;
	}

	m_roomWalls = std::make_shared<sf::RectangleShape>();
	m_roomWalls->setSize(m_roomSize);
	m_roomWalls->setFillColor(sf::Color::Transparent);
	m_roomWalls->setOutlineThickness(4.f);
	m_roomWalls->setOutlineColor(sf::Color::White);
	RenderObject::getInstance().add(m_roomWalls);
}
