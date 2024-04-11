#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameMode.h"
#include "Pawn.h"
#include "levelData.h"

class GamePlay : public GameMode
{
public:
	GamePlay();  // standard constructor
	~GamePlay(); // standard deconstructor (shouldnt be used)

	void resetLevel()override;                         // used to reset the level for each session instead of reconstructing
	void events(sf::Event& t_event)override;           // used to handle all new events outside key presses
	void update()override;         // all update events

private:
	void processKeys(sf::Event& t_event)override;      // handles all key inputs
	void processMouse(sf::Event& t_event)override;     // handles all mouse events

	std::vector<std::shared_ptr<Pawn>> m_pawns;
	levelData m_level;
};

#endif // !GAMEPLAY_H
