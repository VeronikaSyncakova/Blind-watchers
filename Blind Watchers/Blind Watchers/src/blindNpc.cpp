#include "blindNpc.h"
#include "RenderObject.h"
#include "Game.h"
#include "ParticleSpawner.hpp"
#include "simpleMaths.h"

/// <summary>
/// setup the shared pointer for the body
/// </summary>
/// <param name="t_characterData"></param>
blindNpc::blindNpc(npcData& t_characterData) : m_visionCone(t_characterData.position, 100.f, 45.f)
{
	m_body = std::make_shared<body>();
	m_body->initialiseBody(t_characterData);
	m_position = t_characterData.position;

	if (t_characterData.state == "Wander")
		m_currentState = State::Wander;
	else if (t_characterData.state == "Patrol")
		m_currentState = State::Patrol;
	else if (t_characterData.state == "None")
		m_currentState = State::None;

	setPatrolPoints(t_characterData);
	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);

	m_active = true;
}

blindNpc::~blindNpc()
{
}

void blindNpc::update()
{
	if (m_cantFindPlayer >= 0.f)
	{
		m_cantFindPlayer -= Game::deltaTime;
		if (m_cantFindPlayer <= 0.f)
		{
			switch (m_currentState)
			{
			case State::None:
				break;
			case State::Wander:
				m_state = std::make_shared<WanderState>();
				break;
			case State::Patrol:
				m_state = std::make_shared<PatrolState>();
				break;
			default:
				m_state = std::make_shared<NoneState>();
				break;
			}
		}
	}
}

void blindNpc::expire()
{
	m_active = false;
	ParticleSpawner::explode(m_position);
	m_position = sf::Vector2f(-10000.f, -10000.f);
	m_body->m_rectangle->setPosition(m_position);
}

void blindNpc::moveBody(sf::Vector2f const& t_moveVector)
{
	if (RoomPlan::getInstance().collides(m_body->getBody(), m_roomNumber))
	{
		sf::Vector2f deflection = RoomPlan::getInstance().deflectVector(m_body->getBody(), m_roomNumber);
		m_position += deflection * m_maxSpeed * Game::deltaTime;
		if (auto t = std::dynamic_pointer_cast<PatrolState>(m_state))
		{
			t->skipPoint(std::make_shared<blindNpc>(*this));
		}
	}
	else
	{
		m_position += t_moveVector * m_maxSpeed * Game::deltaTime;
	}
	if(!m_cantFindPlayer <= 0.f)
	{
		float travelDegrees = math::displacementToDegrees(t_moveVector);
		//DEBUG_MSG(travelDegrees);

		if (travelDegrees >= 45.f && travelDegrees < 135.f)
		{
			m_visionCone.setRotation(90.f);
		}
		else if (travelDegrees >= 135.f && travelDegrees < 225.f)
		{
			m_visionCone.setRotation(180.f);
		}
		else if (travelDegrees >= 225.f && travelDegrees < 315.f)
		{
			m_visionCone.setRotation(270.f);
		}
		else
		{
			m_visionCone.setRotation(0.f);
		}
	}

	m_visionCone.moveCone(m_position);
	m_body->moveBody(m_position);
}

npcData blindNpc::getData()
{
	npcData currentData;
	currentData.position = m_body->getBody().getPosition();
	currentData.color = m_body->getBody().getFillColor();
	currentData.size = m_body->getBody().getSize();
	currentData.speed = m_moveSpeed;
	currentData.patrolPoints = m_patrolPoints;
	return currentData;
}

bool blindNpc::checkFoundPlayer(sf::FloatRect t_playerBounds)
{
	if (m_visionCone.checkCollision(t_playerBounds))
	{
		m_cantFindPlayer = 2.f;
		m_state = std::make_shared<SeekPlayer>();
		return true;
	}
	return false;
}

void blindNpc::rotate(float t_angle)
{
	m_visionCone.setRotation(t_angle);
}

int blindNpc::getCurrentRoom()
{
	return m_roomNumber;
}

void blindNpc::position(sf::Vector2f& t_position)
{
	m_position = t_position;
	m_visionCone.moveCone(m_position);
	m_body->m_rectangle->setPosition(m_position);
	m_roomNumber = RoomPlan::getInstance().getRoomNumber(m_position);
}

void blindNpc::writeYAML(YAML::Emitter& t_out)
{
	//position
	t_out << YAML::BeginMap;
	t_out << YAML::Key << "position" << YAML::Value << YAML::BeginMap;
	t_out << YAML::Key << "x" << YAML::Value << m_body->getBody().getPosition().x;
	t_out << YAML::Key << "y" << YAML::Value << m_body->getBody().getPosition().y;
	//t_out << YAML::EndMap;
	t_out << YAML::EndMap;
	//color
	//t_out << YAML::BeginMap;
	t_out << YAML::Key << "colour" << YAML::Value << YAML::BeginMap;
	t_out << YAML::Key << "r" << YAML::Value << static_cast<int>(m_body->getBody().getFillColor().r);
	t_out << YAML::Key << "g" << YAML::Value << static_cast<int>(m_body->getBody().getFillColor().g);
	t_out << YAML::Key << "b" << YAML::Value << static_cast<int>(m_body->getBody().getFillColor().b);
	t_out << YAML::Key << "a" << YAML::Value << static_cast<int>(m_body->getBody().getFillColor().a);
	//t_out << YAML::EndMap;
	t_out << YAML::EndMap;
	//size
	//t_out << YAML::BeginMap;
	t_out << YAML::Key << "size" << YAML::Value << YAML::BeginMap;
	t_out << YAML::Key << "x" << YAML::Value << m_body->getBody().getSize().x;
	t_out << YAML::Key << "y" << YAML::Value << m_body->getBody().getSize().y;
	//t_out << YAML::EndMap;
	t_out << YAML::EndMap;
	//speed
	//t_out << YAML::BeginMap;
	t_out << YAML::Key << "speed" << YAML::Value << m_maxSpeed;
	//t_out << YAML::EndMap;
	//texture
	//t_out << YAML::BeginMap;
	t_out << YAML::Key << "texture" << YAML::Value << "unavailableCurrently.png";
	//t_out << YAML::EndMap;
	//pathing type
	//t_out << YAML::BeginMap;
	t_out << YAML::Key << "pathingType";
	if(m_currentState==State::Wander)
		t_out<<YAML::Value << "Wander";
	else if (m_currentState == State::Patrol)
		t_out << YAML::Value << "Patrol";
	if (m_currentState == State::None)
		t_out << YAML::Value << "None";
	//t_out << YAML::EndMap;
	//paths
	//t_out << YAML::BeginMap;
	t_out << YAML::Key << "paths" << YAML::Value;
	t_out << YAML::BeginSeq;
	for (unsigned i = 0; i < m_patrolPoints.size(); i++)
	{
		sf::Vector2f patrolPointsInRoom = m_patrolPoints.at(i) + RoomPlan::getInstance().getRoomPosition(m_roomNumber);
		t_out<<YAML::BeginMap << YAML::Key << "point" << YAML::BeginMap;
		t_out << YAML::Key << "x" << YAML::Value << patrolPointsInRoom.x;
		t_out << YAML::Key << "y" << YAML::Value << patrolPointsInRoom.y;
		t_out << YAML::EndMap << YAML::EndMap;
	}
	t_out << YAML::EndSeq;

	t_out << YAML::EndMap;
}

void blindNpc::huntPlayer()
{
	m_cantFindPlayer = 0.5f;
	m_state = std::make_shared<SeekPlayer>();
}

void blindNpc::setPatrolPoints(npcData& t_characterData)
{
	m_patrolPoints = t_characterData.patrolPoints;
}

/// <summary>
/// read the data from the npcData struct and set the rectangles properties based on that
/// </summary>
/// <param name="t_data"></param>
void body::initialiseBody(npcData& t_data)
{
	m_rectangle = std::make_shared<sf::RectangleShape>();

	sf::Color bodyColor = t_data.color;
	m_rectangle->setFillColor(bodyColor);

	m_rectangle->setPosition(t_data.position);

	m_rectangle->setSize(t_data.size);
	m_rectangle->setOrigin(t_data.size / 2.f);

	RenderObject::getInstance().add(m_rectangle);
}

void body::moveBody(sf::Vector2f const& t_newPos)
{
	m_rectangle->setPosition(t_newPos);
}

sf::RectangleShape body::getBody()
{
	return *m_rectangle;
}
