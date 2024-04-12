#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct npcData
{
	sf::Vector2f position;
	sf::Color color;
	sf::Vector2f size;
	float speed;

	std::vector<sf::Vector2f> patrolPoints;
};

struct levelData
{
	std::vector<npcData> m_npcs;
};