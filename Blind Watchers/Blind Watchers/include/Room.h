#pragma once 
#include "RenderObject.h"
struct RoomData
{
	std::string m_roomType="TopRight";
	float m_sizeX=800.f;
	float m_sizeY=500.f;
	float m_positionX=0.f;
	float m_positionY=0.f;
};

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