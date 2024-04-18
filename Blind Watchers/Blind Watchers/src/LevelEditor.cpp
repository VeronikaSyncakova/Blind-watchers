#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	loadData();
	zoomOut();
}

LevelEditor::~LevelEditor()
{
	saveData();
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
	switch (m_viewType)
	{
	case ViewType::ZoomOut:
		if (m_zoomAmount < 2.f)
		{
			m_zoomAmount += 0.1f;
			RenderObject::getInstance().zoomCamera(m_zoomAmount, sf::Vector2f(1700.f,900.f));
		}
		break;
	case ViewType::ZoomIn:
		if (m_zoomAmount > 1.f)
		{
			m_zoomAmount -= 0.1f;
			RenderObject::getInstance().zoomCamera(m_zoomAmount, m_selectedRoomCenter);
		}
		buttonCollision();
		break;
	default:
		break;
	}
	
}

void LevelEditor::zoomIn(int& t_roomNum)
{
	m_viewType = ViewType::ZoomIn;
	for (unsigned int i = 0; i < m_pawnButtons.size(); i++)
	{
		m_pawnButtons.at(i).m_bounds->setOutlineColor(sf::Color::White);
		m_pawnButtons.at(i).m_bounds->setFillColor(sf::Color(255, 255, 255, 80));
	}
	RoomPlan::getInstance().hovering(-1);
	m_selectedRoomCenter= RoomPlan::getInstance().getRoomCenter(t_roomNum);
}

void LevelEditor::zoomOut()
{
	m_viewType = ViewType::ZoomOut;
	for (unsigned int i = 0; i < m_pawnButtons.size(); i++)
	{
		m_pawnButtons.at(i).m_bounds->setOutlineColor(sf::Color::Transparent);
		m_pawnButtons.at(i).m_bounds->setFillColor(sf::Color::Transparent);
	}
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
		findMousePosView(t_event);
		if(m_viewType==ViewType::ZoomOut)
			RoomPlan::getInstance().hovering(RoomPlan::getInstance().getRoomNumber(m_mousePosView));
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		
		if (m_viewType==ViewType::ZoomOut)
		{
			//RoomPlan::getInstance().selectedRoom(RoomPlan::getInstance().getRoomNumber(m_mousePosView));
			int roomNum = RoomPlan::getInstance().getRoomNumber(m_mousePosView);
			zoomIn(roomNum);
		}
		else if(m_viewType == ViewType::ZoomIn)
		{
			performButtonAction();

			for (unsigned int i = 0; i < m_pawnButtons.size(); i++)
			{
				// set the outline to yellow if selected
				if (m_pawnButtons.at(i).m_highlighted)
				{
					m_pawnButtons.at(i).m_bounds->setOutlineColor(sf::Color::Yellow);
					buttonAction(i);
				}
				else
				{
					m_pawnButtons.at(i).m_bounds->setOutlineColor(sf::Color::White);
				}

			}
			
		}

	}
}

void LevelEditor::loadData()
{
	// loads the level
	yamlLoader::loadLevelData(m_level, 1);

	//creates room plan
	RoomPlan::getInstance().init(m_level);

	//load medication
	m_medication.initialise(m_level.m_meds);

	// loads player
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	StateManager::changeCommand(State::PlayerInput, player);

	m_pawns.push_back(player);

	for (unsigned int i = 0; i < m_level.m_npcs.size(); i++)
	{
		std::shared_ptr<blindNpc> newNpc;
		newNpc = std::make_shared<blindNpc>(m_level.m_npcs.at(i));
		if (m_level.m_npcs.at(i).state == "Wander")
			StateManager::changeCommand(State::Wander, newNpc);
		else if (m_level.m_npcs.at(i).state == "Patrol")
			StateManager::changeCommand(State::Patrol, newNpc);
		else if (m_level.m_npcs.at(i).state == "None")
			StateManager::changeCommand(State::None, newNpc);

		m_pawns.push_back(newNpc);
	}

	//loads sample npc types for buttons
	levelData npcData;
	yamlLoader::loadNpcData(npcData, 1);

	//sample medData
	levelData medData;
	yamlLoader::loadMedData(medData, 1);
	m_medData = medData.m_meds.at(0);

	//button size and spacing
	float width = 100.f;
	float height = 200.f / (PAWN_BUTTONS);
	float spacing = (SCREEN_HEIGHT / 2.f) / (PAWN_BUTTONS + 1);

	for (int i=0; i<PAWN_BUTTONS; i++)
	{
		std::shared_ptr<sf::RectangleShape> pawnBox;
		pawnBox = std::make_shared<sf::RectangleShape>();

		pawnBox->setSize(sf::Vector2f(width, height));
		pawnBox->setPosition(width,(i + 1) * spacing);
		pawnBox->setOrigin(pawnBox->getGlobalBounds().width / 2.f, pawnBox->getGlobalBounds().height / 2.f);
		pawnBox->setFillColor(sf::Color(255, 255, 255, 80));
		pawnBox->setOutlineColor(sf::Color::White);
		pawnBox->setOutlineThickness(2u);

		RenderObject::getInstance().addHUD(pawnBox);

		pawnButton newPawnButton;
		newPawnButton.m_bounds = pawnBox;
		m_pawnButtons.push_back(newPawnButton);
	}
	m_pawnButtons.at(1).m_pawn = std::make_shared<blindNpc>(npcData.m_npcs.at(0));//m_pawns.at(1); //std::make_shared<blindNpc>(m_level.m_npcs.at(0));
	m_pawnButtons.at(2).m_pawn = std::make_shared<blindNpc>(npcData.m_npcs.at(1));//m_pawns.at(2); //std::make_shared<blindNpc>(m_level.m_npcs.at(1));

}

void LevelEditor::saveData()
{
	// A YAML::Emitter acts as a YAML output stream 	
	YAML::Emitter out;
	out << YAML::BeginMap;
	//npcs
	out << YAML::Key << "npc";
	out << YAML::Key;
	out << YAML::BeginSeq;
	for (unsigned i = 1; i < m_pawns.size(); i++)
	{
		m_pawns.at(i)->writeYAML(out);
	}
	out << YAML::EndSeq;
	//medication
	out << YAML::Key << "medication";
	out << YAML::Key;
	out << YAML::BeginSeq;
	m_medication.writeYAML(out);
	out << YAML::EndSeq;

	out << YAML::EndMap;

	// Now write it to a file..
	std::string file = "./ASSETS/DATA/LEVEL/level0.yaml";
	std::ofstream fout(file); // This is the path to the YAML file

	fout << out.c_str() << std::endl;
	fout.close();
	
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

void LevelEditor::buttonAction(int t_buttonNum)
{
	if (t_buttonNum == 0) //medication
	{
		m_pawnButtons.at(0).m_selected = true;
	}
	else if (t_buttonNum == 1) //npc1
	{
		//getnpcData from the npcthat is sored in the button
		npcData data = std::dynamic_pointer_cast<blindNpc>(m_pawnButtons.at(1).m_pawn)->getData();
		//make new npc 
		std::shared_ptr<Pawn> newNpc = std::make_shared<blindNpc>(data);
		StateManager::changeCommand(m_pawnButtons.at(1).m_pawn->getState(), newNpc);
		//newNpc->position(m_mousePosView);
		m_pawns.push_back(newNpc);
		m_pawnButtons.at(1).m_selected = true;
	}
	else if (t_buttonNum == 2) //npc2
	{
		npcData data = std::dynamic_pointer_cast<blindNpc>(m_pawnButtons.at(2).m_pawn)->getData();

		std::shared_ptr<Pawn> newNpc = std::make_shared<blindNpc>(data);
		StateManager::changeCommand(m_pawnButtons.at(2).m_pawn->getState(), newNpc);
		//newNpc->position(m_mousePosView);
		m_pawns.push_back(newNpc);
		m_pawnButtons.at(2).m_selected = true;
	}
	else if(t_buttonNum==3) //delete objects
	{
		m_pawnButtons.at(3).m_selected = true;
	}
	/*
	else if (t_buttonNum == 4) //medication
	{
		m_pawnButtons.at(4).m_selected = true;
	}*/
	else if (t_buttonNum == PAWN_BUTTONS-1) //zoom out
	{
		zoomOut();
	}
}

void LevelEditor::performButtonAction()
{
	bool canPlace = false;
	if (RoomPlan::getInstance().getRoomNumber(m_mousePosView) != -1)
		canPlace = true;

	//place the objects to the level
	if (m_pawnButtons.at(0).m_selected && canPlace) //place medication
	{
		m_medData.position = m_mousePosView;
		m_medication.addMedication(m_medData);
		m_pawnButtons.at(0).m_selected = false;
	}
	else if (m_pawnButtons.at(1).m_selected && canPlace) //npc1
	{
		m_pawns.at(m_pawns.size() - 1)->position(m_mousePosView);
		m_pawnButtons.at(1).m_selected = false;
	}
	else if (m_pawnButtons.at(2).m_selected && canPlace) //npc2
	{
		m_pawns.at(m_pawns.size() - 1)->position(m_mousePosView);
		m_pawnButtons.at(2).m_selected = false;
	}
	else if (m_pawnButtons.at(3).m_selected) //delete objects
	{
		for (unsigned i = 1; i < m_pawns.size(); i++) //starting at 1 because 0 is a player and you can not delete player
		{
			//delete the chosen onject
			if (m_pawns.at(i)->getBounds().contains(m_mousePosView))
			{
				m_pawns.erase(m_pawns.begin()+i);
				m_pawnButtons.at(3).m_selected = false;
				break;
			}
		}
		if(m_medication.erase(m_mousePosView))
			m_pawnButtons.at(3).m_selected = false;
	}
	/*
	else if (m_pawnButtons.at(4).m_selected && canPlace) //medication
	{
		m_medData.position = m_mousePosView;
		m_medication.addMedication(m_medData);
		m_pawnButtons.at(4).m_selected = false;
	}
	*/
}
