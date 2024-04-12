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

	Room();
	void init(RoomData& data);
	bool inside(sf::Vector2f t_position);
	bool checkCollision(sf::RectangleShape& t_object);
	sf::Vector2f deflectVector(sf::RectangleShape& t_object);

private:
	std::shared_ptr<sf::RectangleShape> m_roomWalls; //body of the room
	RoomType m_roomType; //where it is positioned
	sf::Vector2f m_roomSize;
	sf::Vector2f m_position;
};