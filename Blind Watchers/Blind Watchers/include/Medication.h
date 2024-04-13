#pragma once

#include <SFML/Graphics.hpp>
#include "levelData.h"
#include "AnimatedSprite.h"

struct medBody
{
	sf::Vector2f pos() { return sprite.getPosition(); }
	sf::FloatRect bounds() { return interactionBounds.getGlobalBounds(); }

	sf::Texture texture;
	sf::Sprite sprite;

	sf::RectangleShape interactionBounds;
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
	void checkInteract();
private:
	std::vector<medBody> m_meds;

	sf::Texture m_pressButtonT;
	std::shared_ptr<AnimatedSprite> m_pressButton;
};