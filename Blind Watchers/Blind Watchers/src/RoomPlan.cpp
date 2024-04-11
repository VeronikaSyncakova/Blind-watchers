#include "RoomPlan.h"

RoomPlan::RoomPlan()
{
	RoomData data;
	DoorData doorData;
	for (int i = 0; i < 4; i++)
	{
		m_rooms.emplace_back(data);
		m_doors.emplace_back(doorData);
	}	
}
