#include "CharacterSelection.h"
#include "Game.h"
#include "GlobalFontStorage.h"

/// <summary>
/// default constructor
/// </summary>
CharacterSelection::CharacterSelection()
{
	spawnSelectionBoxes();

	m_name = std::make_shared<sf::Text>();

	m_name->setFont(*GlobalFontStorage::getInstance().getFont());
	m_name->setCharacterSize(72u);
	m_name->setFillColor(sf::Color::White);
	m_name->setOutlineColor(sf::Color::Black);
	m_name->setOutlineThickness(0.5f);
	m_name->setString("                                                  SELECT A CHARACTER BELOW");
	m_name->setOrigin(m_name->getGlobalBounds().width / 2.f, m_name->getGlobalBounds().height / 2.f);
	m_name->setPosition(SCREEN_WIDTH / 2.f - 600.f, 400.f);

	RenderObject::getInstance().addHUD(m_name);

	PlayerData data;

	for (int i = 0; i < PLAYER_TYPE_AMT; i++)
	{
		data = static_cast<PlayerType>(i);

		m_nameS.push_back(data.m_name);

		m_assets.emplace_back();
		if (!m_assets.at(i).loadFromFile("ASSETS\\IMAGES\\Misc\\" + m_nameS.at(i) + ".png"))
			DEBUG_MSG("COULDNT LOAD PLAYER");
	}
	m_currentSprite = std::make_shared<AnimatedSprite>(0.2f, m_assets.at(0));

	m_currentSprite->addFrame(sf::IntRect(0, 0, 35, 35));
	m_currentSprite->addFrame(sf::IntRect(35, 0, 35, 35));
	m_currentSprite->addFrame(sf::IntRect(0, 0, 35, 35));
	m_currentSprite->addFrame(sf::IntRect(70, 0, 35, 35));


	m_currentSprite->setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f + 400.f, -400.f));
	m_currentSprite->setOrigin(sf::Vector2f(17.5f, 17.5f));
	m_currentSprite->setScale(sf::Vector2f(8.f, 8.f));
	m_currentSprite->setRotation(90.f);

	RenderObject::getInstance().addHUD(m_currentSprite);

	m_bg = std::make_shared<sf::Sprite>();

	m_assets.emplace_back();

	m_assets.emplace_back();
	m_Select = std::make_shared<sf::Sprite>();
	if (!m_assets.at(m_assets.size() - 1).loadFromFile("ASSETS\\IMAGES\\Misc\\CharacterSelect.png"))
		DEBUG_MSG("COULDNT LOAD CHARACTER SELECT");
	m_Select->setTexture(m_assets.at(m_assets.size() - 1));
	m_Select->setPosition(400.f,850.f);


	RenderObject::getInstance().add(m_Select);

	if (!m_assets.at(m_assets.size() - 2).loadFromFile("ASSETS\\IMAGES\\Misc\\background.png"))
		DEBUG_MSG("COULDNT LOAD BackGround");
	m_assets.at(m_assets.size() - 2).setRepeated(true);
	m_bg->setTexture(m_assets.at(m_assets.size() - 2));
	m_bg->setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	RenderObject::getInstance().addBG(m_bg);
}

/// <summary>
/// default deconstructor
/// </summary>
CharacterSelection::~CharacterSelection()
{
}


/// <summary>
/// resets all values to default as needed
/// </summary>
void CharacterSelection::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void CharacterSelection::events(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type || sf::Event::KeyReleased == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}
	else
	{
		processMouse(t_event);
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void CharacterSelection::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void CharacterSelection::update()
{
	m_currentSprite->update();

	if (m_characterSelected)
	{
		m_playButton.updateFrame();
	}
	
	buttonCollision();
	
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void CharacterSelection::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);

		if(m_characterSelected)
			m_playButton.checkBounds(m_mousePos);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		for (unsigned int i = 0; i < m_selectionBoxes.size(); i++)
		{
			// check collision with the play button
			if (m_characterSelected)
				if (m_playButton.releaseButton())
					Game::s_selectedPlayer = m_chosenData;

			// set the outline to yellow if selected
			if (m_selectionBoxes.at(i).m_highlighted)
			{
				m_chosenData = m_selectionBoxes.at(i).m_containedPlayer;
				m_selectionBoxes.at(i).m_bounds->setOutlineColor(sf::Color::Yellow);
				m_characterSelected = true;

				m_currentSprite->setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f + 400.f, 400.f));
				m_currentSprite->setTexture(m_assets.at(i));
				m_name->setString(m_nameS.at(i));
				m_name->setOrigin(m_name->getGlobalBounds().width / 2.f, m_name->getGlobalBounds().height / 2.f);

				
				initialisePlayButton();
			}
			else
			{
				m_selectionBoxes.at(i).m_bounds->setOutlineColor(sf::Color::White);
			}
		}
	}
}

/// <summary>
/// @brief spawn all the selection boxes based off the dimensions
/// </summary>
void CharacterSelection::spawnSelectionBoxes()
{
	for (int i = 0; i < PLAYER_TYPE_AMT; i++)
	{
		std::shared_ptr<sf::RectangleShape> selectionBox;
		selectionBox = std::make_shared<sf::RectangleShape>();


		float width = 400.f / PLAYER_TYPE_AMT;
		float height = 150.f;
		selectionBox->setSize(sf::Vector2f(width, height));


		float spacing = SCREEN_WIDTH / (PLAYER_TYPE_AMT + 1);
		selectionBox->setPosition((i + 1) * spacing, SCREEN_HEIGHT / 2.f + 400.f);


		selectionBox->setOrigin(selectionBox->getGlobalBounds().width / 2.f, selectionBox->getGlobalBounds().height / 2.f);
		selectionBox->setFillColor(sf::Color(255, 255, 255, 80));
		selectionBox->setOutlineColor(sf::Color::White);
		selectionBox->setOutlineThickness(1u);

		RenderObject::getInstance().add(selectionBox);

		characterSelectionBox newCharacterBox;
		newCharacterBox.m_bounds = selectionBox;
		newCharacterBox.m_containedPlayer = static_cast<PlayerType>(i);
		m_selectionBoxes.push_back(newCharacterBox);
	}
}

/// <summary>
/// @brief check collision with the mouse
/// </summary>
void CharacterSelection::buttonCollision()
{
	float highlightSpeed = 0.03f;
	for (unsigned int i = 0; i < m_selectionBoxes.size(); i++)
	{
		// name changes
		characterSelectionBox& characterBox = m_selectionBoxes.at(i);
		std::shared_ptr<sf::RectangleShape> box = characterBox.m_bounds;
		sf::FloatRect& boxBounds = box->getGlobalBounds();

		// colliding
		if (boxBounds.contains(m_mousePos))
		{
			// is the mouse in the box?
			characterBox.m_highlighted = true;
			if (characterBox.m_highlightAmt < 1.f)
			{
				characterBox.m_highlightAmt += highlightSpeed;
				if (characterBox.m_highlightAmt > 1.0f)
				{
					characterBox.m_highlightAmt = 1.0f;
				}
			}
		}
		// not colliding
		else
		{
			characterBox.m_highlighted = false;
			if (characterBox.m_highlightAmt > 0.0f)
			{
				characterBox.m_highlightAmt -= highlightSpeed * 2.f;
				if (characterBox.m_highlightAmt < 0.0f)
				{
					characterBox.m_highlightAmt = 0.0f;
				}
			}
		}

		// set highlight based off highlight percentage
		int highlight = static_cast<int>(characterBox.m_highlightAmt * 190 + 30);
		box->setFillColor(sf::Color(255, 255, 255, highlight));
	}
}

/// <summary>
/// @brief spawn a new play button, after the character is selected
/// </summary>
void CharacterSelection::initialisePlayButton()
{

	if (!m_playButtonTexture.loadFromFile("ASSETS\\IMAGES\\Buttons\\rotate_button.png")) //
	{
		DEBUG_MSG("COULDNT FIND BUTTON");
		exit(1);
	}
	else
	{
		//m_playButton.at(i).init(m_buttonTexture, sf::Vector2i(320, 96), sf::Vector2f(-1.f, 600.f + (100 * i)), 6, 0.5f);
		m_playButton.init(m_playButtonTexture, sf::Vector2i(256, 128), sf::Vector2f(SCREEN_WIDTH - 300.f, SCREEN_HEIGHT - 200.f), 4, 0.5f);

		//m_playButton.changeFrameHeight(1);

		m_playButton.setFunction([]() -> void { Game::s_changeGameMode = true; Game::s_currentGameMode = GameModeClass::Gameplay; });
	}
}

