#pragma once
#include"GameMode.h"
#include "Player.h"
#include "blindNpc.h"
#include "levelData.h"
#include "RoomPlan.h"
#include "YamlLoader.h"

struct pawnButton
{
	std::shared_ptr<sf::RectangleShape> m_bounds;
	float m_highlightAmt = 0.0f;
	bool m_highlighted = false;
	std::shared_ptr<Pawn> m_pawn;
};

class LevelEditor : public GameMode
{
public:
	LevelEditor();
	~LevelEditor();

	virtual void resetLevel() override;                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event) override;           // used to handle all new events outside key presses
	virtual void update() override;         // all update events

private:
	virtual void processKeys(sf::Event& t_event) override;      // handles all key inputs
	virtual void processMouse(sf::Event& t_event) override;     // handles all mouse events
	
	void loadData();
	void saveData();

	void buttonCollision();

	std::vector<std::shared_ptr<Pawn>> m_pawns;
	levelData m_level;
	std::vector<pawnButton> m_pawnButtons;
	const int PAWN_BUTTONS{ 3 };

};