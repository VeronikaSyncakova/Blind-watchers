#include "GameWin.h"
#include "GlobalFontStorage.h"
#include "RenderObject.h"
#include "ParticleSpawner.hpp"
#include "Game.h"

/// <summary>
/// default constructor
/// </summary>
GameWin::GameWin()
{
	m_dispText = std::make_shared<sf::Text>();

	m_dispText->setFont(*GlobalFontStorage::getInstance().getFont());
	m_dispText->setCharacterSize(48u);
	m_dispText->setFillColor(sf::Color::Green);
	m_dispText->setOutlineColor(sf::Color::Black);
	m_dispText->setOutlineThickness(0.5f);
	m_dispText->setString("YOU WIN");
	m_dispText->setOrigin(m_dispText->getGlobalBounds().width / 2.f, m_dispText->getGlobalBounds().height / 2.f);
	m_dispText->setPosition(SCREEN_WIDTH / 2.f, 200.f);

	RenderObject::getInstance().addHUD(m_dispText);
}

/// <summary>
/// default deconstructor
/// </summary>
GameWin::~GameWin()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void GameWin::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GameWin::events(sf::Event& t_event)
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
void GameWin::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GameWin::update()
{
	ParticleSystem::getInstance().update();

	m_moreFireworks -= Game::deltaTime;

	if (m_moreFireworks <= 0.f)
	{
		m_moreFireworks = 0.5f;
		ParticleSpawner::explode(sf::Vector2f(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT), 200);
	}
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GameWin::processMouse(sf::Event& t_event)
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
		
	}
}

