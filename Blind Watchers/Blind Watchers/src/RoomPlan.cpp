#include "RoomPlan.h"
#include "DEBUG.h"

RoomPlan::RoomPlan()
{
}

void RoomPlan::init(levelData& t_data)
{
	if(!m_roomBackgroundTexture.loadFromFile("ASSETS\\IMAGES\\Misc\\background.png"))
		DEBUG_MSG("COULDNT LOAD ROOM BACKGROUND");
	if (!m_doorTexture.loadFromFile("ASSETS\\IMAGES\\Misc\\door.png"))
		DEBUG_MSG("COULDNT LOAD DOOR");

	//temporary door vector where I load the door data
	std::vector<Door> doors;
	for (unsigned i = 0; i < t_data.m_doors.size(); i++)
	{
		Door newDoor;
		newDoor.init(t_data.m_doors.at(i),m_doorTexture);
		doors.push_back(newDoor);
	}

	//loading the rooms and creating doors
	for (unsigned i = 0; i < t_data.m_rooms.size(); i++)
	{
		Room newRoom;
		newRoom.init(t_data.m_rooms.at(i), m_roomBackgroundTexture);
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

sf::Vector2f RoomPlan::getRoomCenter(int t_roomNum)
{
	return m_rooms[t_roomNum].getCenter();
}

sf::Vector2f RoomPlan::getRoomPosition(int& t_roomNum)
{
	return m_rooms[t_roomNum].getPosition();;
}

bool RoomPlan::collides(sf::RectangleShape& t_object, int& t_roomNum)
{
	if (t_roomNum != -1)
		return m_rooms.at(t_roomNum).checkCollision(t_object);
	else
		return false;
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

sf::FloatRect RoomPlan::getRoom(int& t_roomNum)
{
	return m_rooms[t_roomNum].getRoomBounds();
}

void RoomPlan::selectedRoom(int t_num)
{
	for (int i = 0; i < m_rooms.size(); i++)
	{
		if(i==t_num)
			m_rooms[t_num].changeHighlite(sf::Color::Yellow);
		else
			m_rooms[i].changeHighlite(sf::Color::White);
	}
	
}

void RoomPlan::hovering(int t_roomNum)
{
	for (int i = 0; i < m_rooms.size(); i++)
	{
		if (i == t_roomNum)
			m_rooms[t_roomNum].changeColor(sf::Color(255,255,255,30));
		else
			m_rooms[i].changeColor(sf::Color::Transparent);
	}
}
