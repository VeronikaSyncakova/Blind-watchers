#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct npcData
{
	sf::Vector2f position;
	sf::Color color;
	sf::Vector2f size;
	float speed;
};

struct levelData
{
	std::vector<npcData> m_npcs;
	std::vector<RoomData> m_rooms;
	std::vector<DoorData> m_doors;
};

struct RoomData
{
	std::string m_roomType = "TopRight";
	float m_sizeX = 800.f;
	float m_sizeY = 500.f;
	float m_positionX = 0.f;
	float m_positionY = 0.f;
};

struct DoorData
{
	std::string m_doorType = "East";
	float m_positionX = 30.f;
	float m_positionY = 30.f;
	float m_rotation = 0.f;
};