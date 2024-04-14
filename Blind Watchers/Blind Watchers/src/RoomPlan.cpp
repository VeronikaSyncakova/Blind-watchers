#include "RoomPlan.h"

RoomPlan::RoomPlan()
{
}

void RoomPlan::init(levelData& t_data)
{
	//temporary door vector where I load the door data
	std::vector<Door> doors;
	for (unsigned i = 0; i < t_data.m_doors.size(); i++)
	{
		Door newDoor;
		newDoor.init(t_data.m_doors.at(i));
		doors.push_back(newDoor);
	}

	//loading the rooms and creating doors
	for (unsigned i = 0; i < t_data.m_rooms.size(); i++)
	{
		Room newRoom;
		newRoom.init(t_data.m_rooms.at(i));
		m_rooms[i]=newRoom;
		//assigning doors to rooms
		for (Door door : doors)
		{
			if (m_rooms[i].inside(door.getPosition())) //check if the door is in the room
				m_doors[i].push_back(door);
		}
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
	return m_rooms.at(t_roomNum).deflectVector(t_object);
}

bool RoomPlan::usesDoor(sf::RectangleShape& t_object, int& t_roomNum)
{
	for (Door& door : m_doors[t_roomNum])
	{
		if (door.collides(t_object))
			return true;
	}
	return false;
}

void RoomPlan::selectedRoom(int t_num)
{
	for (int i = 0; i < m_rooms.size(); i++)
	{
		if(i==t_num)
			m_rooms[t_num].changeHighlite(sf::Color::Yellow);
		else
			m_rooms[t_num].changeHighlite(sf::Color::White);
	}
	
}
