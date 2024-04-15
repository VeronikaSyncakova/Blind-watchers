#pragma once

#include "Pawn.h"
#include "levelData.h"

/// <summary>
/// struct holding the visible part of the npc,
/// will contain sprite also
/// </summary>
struct body
{
	void initialiseBody(npcData& t_data);
	void moveBody(sf::Vector2f const& t_newPos);
	sf::RectangleShape getBody();
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

	virtual sf::FloatRect getBounds()override { return m_body->m_rectangle->getGlobalBounds(); }

	npcData getData(); 

	void position(sf::Vector2f& t_position) override;
private:
	void setPatrolPoints(npcData& t_characterData);

	std::shared_ptr<body> m_body;
	float m_maxSpeed{ 100.f };
};