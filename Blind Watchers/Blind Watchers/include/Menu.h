#include "GameMode.h"
#include "Button.h"
#include "SimpleButton.h"

class Menu : public GameMode
{
public:
	Menu();
	~Menu(); 
	
	void resetLevel()override;                         // used to reset the level for each session instead of reconstructing
	void events(sf::Event& t_event)override;           // used to handle all new events outside key presses
	void update()override;         // all update events

private:
	void processKeys(sf::Event& t_event)override;      // handles all key inputs
	void processMouse(sf::Event& t_event)override;     // handles all mouse events

	void mouseButtonDown();
	void mouseButtonUp();

	// ! functions
	sf::Texture m_backgroundTexture;
	std::shared_ptr<sf::Sprite> m_backgroundSprite;

	sf::Texture m_buttonTexture;
	std::vector<Button> m_buttons;
	static const int BUTTON_AMOUNT = 4;

	std::shared_ptr<sf::Font> m_globalFont;
	std::shared_ptr<sf::Text> m_hudText;

	std::shared_ptr<SimpleButton> m_simpleButton;
};

