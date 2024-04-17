#pragma once

#include <SFML/Graphics.hpp>
#include "States.h"
#include "RoomPlan.h"
#include "YamlLoader.h"


class Pawn
{
friend StateManager;
public:
	Pawn();
	~Pawn();

	virtual void update() = 0;

	// normalised vector that the pawn will move along
	virtual void moveBody(sf::Vector2f const& t_moveVector) = 0;

	virtual void expire() = 0;

	bool getActive() { return m_active; }
	virtual sf::FloatRect getBounds() = 0;
	sf::Vector2f getPosition() { return m_position; }
	std::vector<sf::Vector2f> getPatrolPoints() { return m_patrolPoints; }
	State getState() { return m_currentState; }
	std::shared_ptr<AbstractState> getAbstractState() { return m_state; }

	virtual void position(sf::Vector2f& t_position)=0; //position the character to a specific location

	virtual void writeYAML(YAML::Emitter& t_out) = 0; //writing data to yaml

	void applyDamage(int t_damageAmt);
	virtual void rotate(float t_angle) = 0;
private:

protected:
	sf::Vector2f m_position;
	float m_moveSpeed{ 0.f };

	State m_currentState{ State::None };
	std::shared_ptr<AbstractState> m_state;

	bool m_active{ false };
	std::vector<sf::Vector2f> m_patrolPoints;
	
	int m_roomNumber{ 0 }; //number of the room where the pawn currently is

	int m_health{ 100 };
	int m_maxHealth{ 100 };
	sf::Texture m_bodyTexture;
	std::shared_ptr<sf::Sprite> m_bodySprite;
};