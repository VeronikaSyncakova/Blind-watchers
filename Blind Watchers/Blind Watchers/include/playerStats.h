#pragma once

#include "Globals.h"
#include <SFML/Graphics.hpp>
#include "YamlLoader.h"
#include "DEBUG.h"

struct PlayerData
{
	void operator=(PlayerType const& t_rhs)
	{
		switch (t_rhs)
		{
		case PlayerType::Normal:
			m_name = "normal";
			break;
		case PlayerType::Fast:
			m_name = "fast";
			break;
		case PlayerType::Small:
			m_name = "small";
			break;
		default:
			m_name = "normal";
			break;
		}
		yamlLoader::loadPlayerData(*this);

		DEBUG_MSG(m_name);
		DEBUG_MSG(m_speed);
		std::string size = "size x:" + std::to_string(m_size.x) + "\t y:" + std::to_string(m_size.y);
		DEBUG_MSG(size);

	}
	float m_speed = 1.0f;
	sf::Vector2f m_size = { 30.f,30.f };
	sf::Color m_color = sf::Color::White;
	std::string m_name;
	float m_sprintSpeed;
	float m_sprintTime;
};

