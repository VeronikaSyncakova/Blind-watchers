#include "Medication.h"
#include "RenderObject.h"
#include "DEBUG.h"

Medication::Medication()
{
}

Medication::~Medication()
{
}

void Medication::initialise(std::vector<MedData>& t_medData)
{
	if (!m_pressButtonT.loadFromFile("ASSETS\\IMAGES\\Buttons\\FButtonAnim.png"))
	{
		DEBUG_MSG("COULDNT LOAD BUTTON ANIM");
	}

	m_pressButton = std::make_shared<AnimatedSprite>(0.05f, m_pressButtonT);

	m_pressButton->addFrame(sf::IntRect(0, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(64, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(128, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(192, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(256, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(320, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(256, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(192, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(128, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(64, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(0, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(0, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(0, 0, 64, 64));
	m_pressButton->addFrame(sf::IntRect(0, 0, 64, 64));


	m_pressButton->setPosition(sf::Vector2f(200.f, 200.f));

	m_pressButton->setOrigin(sf::Vector2f(32.f,64.f));

	RenderObject::getInstance().add(m_pressButton);

	m_pressButton->setActive(true);
}

void Medication::update()
{
	m_pressButton->update();
}

void Medication::updatePlayerPosition(sf::FloatRect t_playerBounds)
{
	bool inMeds = false;
	for (unsigned int i = 0; i < m_meds.size(); i++)
	{
		if (m_meds.at(i).bounds().intersects(t_playerBounds)) 
		{
			inMeds = true;
			float playerMid = t_playerBounds.getSize().x / 2.f;
			m_pressButton->setPosition(t_playerBounds.getPosition() + sf::Vector2f(playerMid, -50.f));
			//m_pressButton->setActive(true);

			m_meds.at(i).m_inBounds = true;
		}
	}
	if (!inMeds)
	{
		//m_pressButton->setActive(false);
	}
}

void Medication::checkInteract()
{
	for (unsigned int i = 0; i < m_meds.size(); i++)
	{
		if (m_meds.at(i).m_inBounds)
		{
			DEBUG_MSG("picked up item");
		}
	}
}
