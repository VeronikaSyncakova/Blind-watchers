#pragma once
#include <SFML/Graphics.hpp>
#include "RenderObject.h"

struct DoorData
{
	std::string m_doorType="East";
	float m_positionX=30.f;
	float m_positionY=30.f;
	float m_rotation=0.f;
};

class Door
{
public:
	enum class DoorPosition { //on which wall the door is
		West,
		East,
		South,
		North
	};

	Door(DoorData& data);

private:
	sf::Vector2f m_position;
	DoorPosition m_type;
	sf::Vector2f m_size{ 100.f,20.f };
	float m_rotation;
	std::shared_ptr<sf::RectangleShape> m_body;
};