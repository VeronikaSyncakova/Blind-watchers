#pragma once

#include "GameMode.h"
#include "SimpleButton.h"
#include "Button.h"
#include <vector>

// simple struct to hold the information associated with the box
struct characterSelectionBox
{
	std::shared_ptr<sf::RectangleShape> m_bounds;
	float m_highlightAmt = 0.0f;
	bool m_highlighted = false;
	PlayerType m_containedPlayer;
};

class CharacterSelection : public GameMode
{
public:
	CharacterSelection();  // standard constructor
	~CharacterSelection(); // standard deconstructor (shouldnt be used)

	virtual void resetLevel();                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event);           // used to handle all new events outside key presses
	virtual void update();         // all update events
private:
	virtual void processKeys(sf::Event& t_event);      // handles all key inputs
	virtual void processMouse(sf::Event& t_event);     // handles all mouse events

	void spawnSelectionBoxes(); // spawn all boxes
	void buttonCollision(); // collision with the selection box
	void initialisePlayButton(); // spawn in the play button if the character is selected

	std::vector<characterSelectionBox> m_selectionBoxes;

	PlayerType m_chosenData;
	bool m_characterSelected = false;
	Button m_playButton;
	sf::Texture m_playButtonTexture;
};