#pragma once

#include "GameMode.h"

class GameWin : public GameMode
{
public:
	GameWin();  // standard constructor
	~GameWin(); // standard deconstructor (shouldnt be used)

	virtual void resetLevel();                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event);           // used to handle all new events outside key presses
	virtual void update();         // all update events
private:
	virtual void processKeys(sf::Event& t_event);      // handles all key inputs
	virtual void processMouse(sf::Event& t_event);     // handles all mouse events

	std::shared_ptr<sf::Text> m_dispText;
	float m_moreFireworks{ 0.5f };
};