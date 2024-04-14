#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameMode.h"
#include "Pawn.h"
#include "levelData.h"
#include "RoomPlan.h"
#include "Medication.h"
#include "statusBar.h"
#include "Bullet.h"

enum class GameType
{
	Sneak, Shoot
};


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

	void initialiseRandom();

	std::vector<std::shared_ptr<Pawn>> m_pawns;
	levelData m_level;
	Medication m_meds;

	std::shared_ptr<bar> m_medProgress;
	GameType m_currentGameMode{ GameType::Sneak };

	BulletHolder m_bulletManager;
	bool m_shooting{ false };
};

#endif // !GAMEPLAY_H
