#pragma once 
#include "RenderObject.h"
#include "levelData.h"

class Room
{
public:
	enum class RoomType { //where the room is positioned
		TopRight,
		TopLeft,
		BottomRight,
		BottomLeft
	};

	Room(RoomData& data);

private:
	std::shared_ptr<sf::RectangleShape> m_roomWalls; //body of the room
	RoomType m_roomType; //where it is positioned
	sf::Vector2f m_roomSize;
	sf::Vector2f m_position;
};