#pragma once
#include"Room.h"
#include"Door.h"
#include "levelData.h"

//Holds all rooms and doors, manages communication between rooms and doors and player
class RoomPlan
{
public:
	RoomPlan();
	void init(levelData& t_data);

private:
	std::vector<Room> m_rooms;
	std::vector<Door> m_doors;
};