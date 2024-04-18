#include "GameLose.h"
#include "GlobalFontStorage.h"
#include "RenderObject.h"

/// <summary>
/// default constructor
/// </summary>
GameLose::GameLose()
{
	m_dispText = std::make_shared<sf::Text>();

	m_dispText->setFont(*GlobalFontStorage::getInstance().getFont());
	m_dispText->setCharacterSize(48u);
	m_dispText->setFillColor(sf::Color::Red);
	m_dispText->setOutlineColor(sf::Color::Black);
	m_dispText->setOutlineThickness(0.5f);
	m_dispText->setString("YOU LOSE");
	m_dispText->setOrigin(m_dispText->getGlobalBounds().width / 2.f, m_dispText->getGlobalBounds().height / 2.f);
	m_dispText->setPosition(SCREEN_WIDTH / 2.f, 200.f);

	RenderObject::getInstance().addHUD(m_dispText);
}

/// <summary>
/// default deconstructor
/// </summary>
GameLose::~GameLose()
{
}



/// <summary>
/// resets all values to default as needed
/// </summary>
void GameLose::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GameLose::events(sf::Event& t_event)
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
void GameLose::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GameLose::update()
{
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GameLose::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
		findMousePosView(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//mouseButtonUp();
	}
}

