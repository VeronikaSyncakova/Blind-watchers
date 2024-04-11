#pragma once

#include "Pawn.h"
#include "levelData.h"

struct body
{
	void initialiseBody(npcData& t_data);
	void moveBody(sf::Vector2f const& t_newPos);
	std::shared_ptr<sf::RectangleShape> m_rectangle;
};

class blindNpc : public Pawn
{
public:
	blindNpc(npcData& t_characterData);
	~blindNpc();

	virtual void update()override;

	// normalised vector that the pawn will move along
	virtual void moveBody(sf::Vector2f const& t_moveVector)override;
private:
	std::shared_ptr<body> m_body;
	float m_maxSpeed{ 0.f };
};