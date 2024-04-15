#include "GamePlay.h"
#include "YamlLoader.h"
#include "Player.h"
#include "blindNpc.h"
#include "Particles.h"

/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	initialiseRandom();

	// loads the npc
	yamlLoader::loadLevelData(m_level, 1);

	//creates room plan
	RoomPlan::getInstance().init(m_level);

	for (unsigned int i = 0; i < m_level.m_npcs.size(); i++)
	{
		std::shared_ptr<blindNpc> newNpc;
		newNpc = std::make_shared<blindNpc>(m_level.m_npcs.at(i));

		m_pawns.push_back(newNpc);
	}
	StateManager::changeCommand(State::Wander, m_pawns.at(0));
	StateManager::changeCommand(State::Patrol, m_pawns.at(1));

	// loads player, done after so player would be on top
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	StateManager::changeCommand(State::PlayerInput, player);

	m_pawns.push_back(player);
	m_meds.initialise(m_level.m_meds);
	
	resetLevel();
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
	barData newBar;
	newBar.position = sf::Vector2f(20.f, 50.f);
	newBar.size= sf::Vector2f(300.f, 10.f);
	m_medProgress = StatusBar::addNewBar(FillType::FillUp, newBar);
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
	if (sf::Keyboard::F == t_event.key.code)
	{
		if (m_meds.checkInteract())
		{
			float newPercent = 1.f / m_level.m_meds.size();
			DEBUG_MSG(newPercent);
			m_medProgress->changePercent(newPercent);
		}
	}
}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update()
{
	if (m_currentGameMode == GameType::Shoot)
	{
		m_bulletManager.update();
	}

	ParticleSystem::getInstance().update();
	m_meds.update();
	for(std::shared_ptr<Pawn>& p : m_pawns)
	{
		p->update();
		StateManager::update(p);
		if (typeid(*p) == typeid(Player))
		{
			m_meds.updatePlayerPosition(p->getBounds());

			if(m_shooting)
				m_bulletManager.spawnNewBullet(p->getPosition(), m_mousePosView);
		}
	}
	if (m_medProgress->checkEmpty())
	{
		DEBUG_MSG("READY");
		m_currentGameMode = GameType::Shoot;
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
		findMousePosView(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (m_currentGameMode == GameType::Shoot)
		{
			m_shooting = true;
			for (std::shared_ptr<Pawn>& p : m_pawns)
			{
				if (typeid(*p) == typeid(Player))
				{
					m_bulletManager.spawnNewBullet(p->getPosition(), m_mousePosView);
					break;
				}
			}
		}
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		m_shooting = false;
		//mouseButtonUp();
	}
}

// initialise the random seed to a random value
#include <ctime>
#include <cstdlib>
void GamePlay::initialiseRandom()
{
	srand(static_cast<unsigned int> (time(nullptr)));
}
