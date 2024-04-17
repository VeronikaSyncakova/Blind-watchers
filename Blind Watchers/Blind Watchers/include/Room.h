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
	bool inside(sf::Vector2f t_position); //checks if the object is inside of this room
	bool checkCollision(sf::RectangleShape& t_object); //collision check with the walls
	sf::Vector2f deflectVector(sf::RectangleShape& t_object); //returns deflect vector for the colliding object
	void changeHighlite(sf::Color t_color);
	void changeColor(sf::Color t_color);
	sf::Vector2f getCenter();
	sf::Vector2f getPosition();

private:
	std::shared_ptr<sf::RectangleShape> m_roomWalls; //body of the room
	RoomType m_roomType; //where it is positioned
	sf::Vector2f m_roomSize;
	sf::Vector2f m_position;
};