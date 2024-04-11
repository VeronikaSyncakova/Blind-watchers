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
};