#include "RoomPlan.h"

RoomPlan::RoomPlan()
{
}

void RoomPlan::init(levelData& t_data)
{
	for (unsigned i = 0; i < t_data.m_rooms.size(); i++)
	{
		Room newRoom;
		newRoom.init(t_data.m_rooms.at(i));
		m_rooms.push_back(newRoom);
	}
	for (unsigned i = 0; i < t_data.m_doors.size(); i++)
	{
		Door newDoor;
		newDoor.init(t_data.m_doors.at(i));
		m_doors.push_back(newDoor);
	}
}
