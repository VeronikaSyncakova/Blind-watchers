#include "GamePlay.h"
#include "YamlLoader.h"
#include "Player.h"
#include "blindNpc.h"
#include "Particles.h"
#include "DamageApplicator.hpp"
#include "Game.h"

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

		if(m_level.m_npcs.at(i).state=="Wander")
			StateManager::changeCommand(State::Wander, newNpc);
		else if(m_level.m_npcs.at(i).state=="Patrol")
			StateManager::changeCommand(State::Patrol, newNpc);
		else if(m_level.m_npcs.at(i).state == "None")
			StateManager::changeCommand(State::None, newNpc);

		m_pawns.push_back(newNpc);
	}

	// loads player, done after so player would be on top
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	StateManager::changeCommand(State::PlayerInput, player);

	m_pawns.push_back(player);
	m_meds.initialise(m_level.m_meds);
	
	resetLevel();

	std::shared_ptr<damageApplicator> newApplicator;
	newApplicator = std::make_shared<damageApplicator>(m_pawns);
	m_bulletManager.assignDamageApplicator(newApplicator);
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
	m_medProgress = StatusBar::addNewBar(FillType::FillUp, newBar, sf::Color::White);

	barData newStress;
	newStress.position = sf::Vector2f(20.f, 80.f);
	newStress.size = sf::Vector2f(300.f, 10.f);
	m_stressMeter = StatusBar::addNewBar(FillType::Empty, newStress);

	
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
	if (m_stressMeter->checkEmpty())
	{
		Game::s_currentGameMode = GameModeClass::GameLose;
		Game::s_changeGameMode = true;
	}
	int activeRoom = 0;
	bool gameWon = (m_pawns.size() > 1u) ? true : false;

	if (m_currentGameMode == GameType::Shoot)
	{
		m_bulletManager.update();
		for (std::shared_ptr<Pawn>& p : m_pawns)
		{
			if (typeid(*p) == typeid(Player))
			{
				activeRoom = p->getCurrentRoom();
				break;
			}
		}
		for (std::shared_ptr<Pawn>& p : m_pawns)
		{
			if (typeid(*p) == typeid(Player))
			{
				continue;
			}
			if (p->getCurrentRoom() == activeRoom)
			{
				m_bulletManager.checkCollisions(p->getBounds());
			}
		}
		m_bulletManager.checkWallCollision(activeRoom);
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
			for (std::shared_ptr<Pawn>& c : m_pawns)
			{
				if (auto t = std::dynamic_pointer_cast<blindNpc>(c))
				{
					if (t->checkFoundPlayer(p->getBounds()))
						m_stressMeter->changePercent(0.005f);
					if (t->getCurrentRoom() == p->getCurrentRoom() && m_currentGameMode == GameType::Shoot)
					{
						t->huntPlayer();
					}
				}
				if (auto t = std::dynamic_pointer_cast<SeekPlayer>(c->getAbstractState()))
				{
					t->SetPlayer(p->getPosition());
				}
			}
		}
		else
		{
			if (p->getActive())
			{
				gameWon = false;
			}
		}
	}
	if (m_medProgress->checkEmpty())
	{
		m_currentGameMode = GameType::Shoot;
	}
	if (gameWon)
	{
		Game::s_currentGameMode = GameModeClass::GameWin;
		Game::s_changeGameMode = true;
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
