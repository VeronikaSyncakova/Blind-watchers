#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	loadData();
	RenderObject::getInstance().zoomCamera(2.f);
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::resetLevel()
{
}

void LevelEditor::events(sf::Event& t_event)
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

void LevelEditor::update()
{
	buttonCollision();
}

void LevelEditor::processKeys(sf::Event& t_event)
{
	sf::Vector2f moveVector{ 0.f,0.f };
	if (t_event.key.code==sf::Keyboard::W)
	{
		moveVector.y -= 10;
	}
	if (t_event.key.code == sf::Keyboard::S)
	{
		moveVector.y += 10;
	}
	if (t_event.key.code == sf::Keyboard::D)
	{
		moveVector.x += 10;
	}
	if (t_event.key.code == sf::Keyboard::A)
	{
		moveVector.x -= 10;
	}
	RenderObject::getInstance().updateCamera(moveVector);
}

void LevelEditor::processMouse(sf::Event& t_event)
{
	if (sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		bool buttonPressed = false;
		for (unsigned int i = 0; i < m_pawnButtons.size(); i++)
		{
			// set the outline to yellow if selected
			if (m_pawnButtons.at(i).m_highlighted)
			{
				m_pawnButtons.at(i).m_bounds->setOutlineColor(sf::Color::Yellow);
				buttonPressed = true;
			}
			else
			{
				m_pawnButtons.at(i).m_bounds->setOutlineColor(sf::Color::White);
			}
		}
		
		if (!buttonPressed)
		{
			RoomPlan::getInstance().selectedRoom(RoomPlan::getInstance().getRoomNumber(m_mousePos));
		}

	}
}

void LevelEditor::loadData()
{
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

	for (int i=0; i<PAWN_BUTTONS; i++)
	{
		std::shared_ptr<sf::RectangleShape> pawnBox;
		pawnBox = std::make_shared<sf::RectangleShape>();

		float width = 100.f;
		float height = 200.f/PAWN_BUTTONS;
		pawnBox->setSize(sf::Vector2f(width, height));

		float spacing = (SCREEN_HEIGHT/3.f) / (PAWN_BUTTONS + 1);
		pawnBox->setPosition(width,(i + 1) * spacing);

		pawnBox->setOrigin(pawnBox->getGlobalBounds().width / 2.f, pawnBox->getGlobalBounds().height / 2.f);
		pawnBox->setFillColor(sf::Color(255, 255, 255, 80));
		pawnBox->setOutlineColor(sf::Color::White);
		pawnBox->setOutlineThickness(1u);

		RenderObject::getInstance().addHUD(pawnBox);

		pawnButton newPawnButton;
		newPawnButton.m_bounds = pawnBox;
		//newPawnButton.m_pawn = ;
		m_pawnButtons.push_back(newPawnButton);
	}
	m_pawnButtons.at(0).m_pawn = std::make_shared<Player>();
	m_pawnButtons.at(1).m_pawn = std::make_shared<blindNpc>(m_level.m_npcs.at(0));
	m_pawnButtons.at(2).m_pawn = std::make_shared<blindNpc>(m_level.m_npcs.at(1));

}

void LevelEditor::saveData()
{
}

void LevelEditor::buttonCollision()
{
	float highlightSpeed = 0.03f;
	for (unsigned int i = 0; i < m_pawnButtons.size(); i++)
	{
		// name changes
		pawnButton& pawnBox = m_pawnButtons.at(i);
		std::shared_ptr<sf::RectangleShape> box = pawnBox.m_bounds;
		sf::FloatRect& boxBounds = box->getGlobalBounds();

		// colliding
		if (boxBounds.contains(m_mousePos))
		{
			// is the mouse in the box?
			pawnBox.m_highlighted = true;
			if (pawnBox.m_highlightAmt < 1.f)
			{
				pawnBox.m_highlightAmt += highlightSpeed;
				if (pawnBox.m_highlightAmt > 1.0f)
				{
					pawnBox.m_highlightAmt = 1.0f;
				}
			}
		}
		// not colliding
		else
		{
			pawnBox.m_highlighted = false;
			if (pawnBox.m_highlightAmt > 0.0f)
			{
				pawnBox.m_highlightAmt -= highlightSpeed * 2.f;
				if (pawnBox.m_highlightAmt < 0.0f)
				{
					pawnBox.m_highlightAmt = 0.0f;
				}
			}
		}

		// set highlight based off highlight percentage
		int highlight = static_cast<int>(pawnBox.m_highlightAmt * 190 + 30);
		box->setFillColor(sf::Color(255, 255, 255, highlight));
	}
}
