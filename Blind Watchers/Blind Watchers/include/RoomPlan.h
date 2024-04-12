#pragma once
#include"Room.h"
#include"Door.h"
#include "levelData.h"

//Holds all rooms and doors, manages communication between rooms and doors and player
static class RoomPlan
{
public:
	static RoomPlan& getInstance()
	{
		static RoomPlan plan;
		return plan;
	}

	void init(levelData& t_data);
	int getRoomNumber(sf::Vector2f t_position); //returns in which room the position (object) is
	bool collides(sf::RectangleShape& t_object, int& t_roomNum); //collision check with room walls
	sf::Vector2f deflectVector(sf::RectangleShape& t_object, int& t_roomNum); //returns deflect vector for the colliding object

	//deleted functions
	RoomPlan(RoomPlan const&) = delete;
	void operator=(RoomPlan const&) = delete;

private:
	RoomPlan(); //constructor
	//std::vector<Room> m_rooms;
	std::map<int, Room> m_rooms;
	std::vector<Door> m_doors;
};