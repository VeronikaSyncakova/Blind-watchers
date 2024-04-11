#pragma once
#include"Room.h"
#include"Door.h"

//Holds all rooms and doors, manages communication between rooms and doors and player
class RoomPlan
{
public:
	RoomPlan();//RoomData& roomData, DoorData& doorData)

private:
	std::vector<Room> m_rooms;
	std::vector<Door> m_doors;
};