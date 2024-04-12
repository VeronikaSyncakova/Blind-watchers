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
		m_rooms[i]=newRoom;
	}
	for (unsigned i = 0; i < t_data.m_doors.size(); i++)
	{
		Door newDoor;
		newDoor.init(t_data.m_doors.at(i));
		m_doors.push_back(newDoor);
	}
}

int RoomPlan::getRoomNumber(sf::Vector2f t_position)
{
	for (int i=0; i<m_rooms.size(); i++)
	{
		if (m_rooms[i].inside(t_position))
		{
			return i;
		}
	}
	return -1;
}

bool RoomPlan::collides(sf::RectangleShape& t_object, int& t_roomNum)
{
	return m_rooms.at(t_roomNum).checkCollision(t_object);
}

sf::Vector2f RoomPlan::deflectVector(sf::RectangleShape& t_object, int& t_roomNum)
{
	return sf::Vector2f();
}
