#pragma once
#include "RenderObject.h"
#include "levelData.h"

class Door
{
public:
	enum class DoorPosition { //on which wall the door is
		West,
		East,
		South,
		North
	};

	Door();
	void init(DoorData& data);

private:
	sf::Vector2f m_position;
	DoorPosition m_type;
	sf::Vector2f m_size{ 100.f,20.f };
	float m_rotation;
	std::shared_ptr<sf::RectangleShape> m_body;
};