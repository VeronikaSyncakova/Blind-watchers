#pragma once

#include <SFML/Graphics.hpp>
#include "levelData.h"
#include "AnimatedSprite.h"

struct medBody
{
	sf::Vector2f pos() { return sprite->getPosition(); }
	sf::FloatRect bounds() { return interactionBounds->getGlobalBounds(); }
	void uninitialise() { sprite->setPosition(-100000.f, -100000.f); interactionBounds->setPosition(-10000.f, -1000000.f); m_inBounds = false; }

	std::shared_ptr<sf::Sprite> sprite;

	std::shared_ptr<sf::RectangleShape> interactionBounds;
	bool m_inBounds;
};

class Medication
{
public:
	Medication();
	~Medication();

	void initialise(std::vector<MedData>& t_medData);
	void update();
	void updatePlayerPosition(sf::FloatRect t_playerBounds);
	bool checkInteract();
private:
	std::vector<medBody> m_meds;
	sf::Texture m_medTexture;

	sf::Texture m_pressButtonT;
	std::shared_ptr<AnimatedSprite> m_pressButton;
};