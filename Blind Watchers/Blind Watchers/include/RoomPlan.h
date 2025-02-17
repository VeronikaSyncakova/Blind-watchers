#pragma once
#include"Room.h"
#include"Door.h"
#include "levelData.h"
#include <list>

//Holds all rooms and doors, manages communication between rooms and doors and player
class RoomPlan
{
public:
	static RoomPlan& getInstance()
	{
		static RoomPlan plan;
		return plan;
	}

	void init(levelData& t_data);
	int getRoomNumber(sf::Vector2f t_position); //returns in which room the position (object) is
	sf::Vector2f getRoomCenter(int t_roomNum); //returns center point of a room
	sf::Vector2f getRoomPosition(int& t_roomNum); //returns a position of specific room
	bool collides(sf::RectangleShape& t_object, int& t_roomNum); //collision check with room walls
	sf::Vector2f deflectVector(sf::RectangleShape& t_object, int& t_roomNum); //returns deflect vector for the colliding object
	bool usesDoor(sf::RectangleShape& t_object, int& t_roomNum); //checks if the object crosses through the door
	sf::FloatRect getRoom(int& t_roomNum);

	void selectedRoom(int t_num);
	void hovering(int t_roomNum);
	//deleted functions
	RoomPlan(RoomPlan const&) = delete;
	void operator=(RoomPlan const&) = delete;

private:
	RoomPlan(); //constructor
	//std::vector<Room> m_rooms;
	std::map<int, Room> m_rooms;
	//std::vector<Door> m_doors;
	std::map<int, std::list<Door>> m_doors;
	sf::Texture m_roomBackgroundTexture;
	sf::Texture m_doorTexture;
};