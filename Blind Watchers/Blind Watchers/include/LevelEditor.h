#pragma once
#include"GameMode.h"
#include "Player.h"
#include "blindNpc.h"
#include "levelData.h"
#include "RoomPlan.h"
#include "YamlLoader.h"
#include "Medication.h"
#include "GlobalFontStorage.h"
#include "DEBUG.h"

struct pawnButton
{
	std::shared_ptr<sf::RectangleShape> m_bounds;
	float m_highlightAmt = 0.0f;
	bool m_highlighted = false;
	bool m_selected{ false };
	std::shared_ptr<Pawn> m_pawn;
	std::shared_ptr<sf::Text> m_text;

	void string(std::string t_string) {
		m_text->setString(t_string);
		sf::Vector2f size = sf::Vector2f(m_text->getGlobalBounds().width, m_text->getGlobalBounds().height);
		m_text->setOrigin(size / 2.f);
	}
};

struct button
{
	std::shared_ptr<sf::RectangleShape> m_bounds;
	float m_highlightAmt = 0.0f;
	bool m_highlighted = false;
};

class LevelEditor : public GameMode
{
public:
	LevelEditor();
	~LevelEditor();

	virtual void resetLevel() override;                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event) override;           // used to handle all new events outside key presses
	virtual void update() override;         // all update events

	enum class ViewType {
		ZoomIn,
		ZoomOut
	};

	void zoomIn(int& t_roomNum);
	void zoomOut();

private:
	virtual void processKeys(sf::Event& t_event) override;      // handles all key inputs
	virtual void processMouse(sf::Event& t_event) override;     // handles all mouse events
	
	void loadData();
	void saveData();

	void buttonCollision();
	void buttonAction(int t_buttonNum);
	void performButtonAction();

	std::vector<std::shared_ptr<Pawn>> m_pawns;
	levelData m_level;
	std::vector<pawnButton> m_pawnButtons;
	const int PAWN_BUTTONS{ 5 };
	ViewType m_viewType;
	float m_zoomAmount{ 1.f };
	sf::Vector2f m_selectedRoomCenter;
	Medication m_medication;
	MedData m_medData;
	sf::Texture m_medTexture;
	sf::Texture m_deleteTexture;
	std::shared_ptr<sf::Sprite> m_selectedSprite;
};