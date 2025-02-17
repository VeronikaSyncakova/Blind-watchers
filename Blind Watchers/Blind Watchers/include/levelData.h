#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct npcData
{
	sf::Vector2f position;
	sf::Color color;
	sf::Vector2f size;
	float speed;
	std::string state;

	std::vector<sf::Vector2f> patrolPoints;
};

struct RoomData
{
	std::string m_roomType;
	float m_sizeX;
	float m_sizeY;
	float m_positionX;
	float m_positionY;
};

struct DoorData
{
	std::string m_doorType;
	float m_positionX;
	float m_positionY;
	float m_rotation;
};

struct MedData
{
	std::string type;
	sf::Vector2f position;
};

struct levelData
{
	std::vector<npcData> m_npcs;
	std::vector<RoomData> m_rooms;
	std::vector<DoorData> m_doors;
	std::vector<MedData> m_meds;
};
