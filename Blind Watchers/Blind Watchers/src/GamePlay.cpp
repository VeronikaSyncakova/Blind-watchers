#include "GamePlay.h"
#include "YamlLoader.h"
#include "Player.h"
#include "blindNpc.h"

/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	// loads the npc
	yamlLoader::loadLevelData(m_level, 1);

	for (unsigned int i = 0; i < m_level.m_npcs.size(); i++)
	{
		std::shared_ptr<blindNpc> newNpc;
		newNpc = std::make_shared<blindNpc>(m_level.m_npcs.at(i));
		StateManager::changeCommand(State::None, newNpc);

		m_pawns.push_back(newNpc);
	}
	// loads player, done after so player would be on top
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	StateManager::changeCommand(State::PlayerInput, player);

	m_pawns.push_back(player);

	m_roomPlan.init(m_level);

}

/// <summary>
/// default deconstructor
/// </summary>
GamePlay::~GamePlay()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void GamePlay::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GamePlay::events(sf::Event& t_event)
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
void GamePlay::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update()
{
	for(std::shared_ptr<Pawn>& p : m_pawns)
	{
		p->update();
		StateManager::update(p);
	}
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GamePlay::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
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
