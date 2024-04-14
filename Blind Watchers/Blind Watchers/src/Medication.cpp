#include "Medication.h"
#include "RenderObject.h"
#include "DEBUG.h"

Medication::Medication()
{
}

Medication::~Medication()
{
}

// setup sprites, animations, and bounding boxes for the meds
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

	
	if(!m_medTexture.loadFromFile("ASSETS\\IMAGES\\Misc\\pills.png"))
		DEBUG_MSG("COULDNT LOAD PILLS");

	for (auto med : t_medData)
	{
		medBody newMed;
		newMed.m_inBounds = false;

		// setup the sprite
		newMed.sprite = std::make_shared<sf::Sprite>();
		newMed.sprite->setTexture(m_medTexture);
		newMed.sprite->setPosition(med.position);
		newMed.sprite->setOrigin(sf::Vector2f(newMed.sprite->getGlobalBounds().width / 2.f, newMed.sprite->getGlobalBounds().height / 2.f));
		newMed.sprite->setScale(0.5f,0.5f);


		// setup the bounds
		newMed.interactionBounds = std::make_shared<sf::RectangleShape>();
		newMed.interactionBounds->setSize(sf::Vector2f(newMed.sprite->getGlobalBounds().width, newMed.sprite->getGlobalBounds().height) + sf::Vector2f(40.f, 40.f));
		newMed.interactionBounds->setFillColor(sf::Color::Transparent);
		newMed.interactionBounds->setOutlineColor(sf::Color::White);
		newMed.interactionBounds->setOutlineThickness(1.f);
		newMed.interactionBounds->setOrigin(sf::Vector2f(newMed.interactionBounds->getGlobalBounds().width / 2.f, newMed.interactionBounds->getGlobalBounds().height / 2.f));
		newMed.interactionBounds->setPosition(med.position);


		RenderObject::getInstance().addBG(newMed.interactionBounds);
		RenderObject::getInstance().addBG(newMed.sprite);

		m_meds.push_back(newMed);
	}

	m_pressButton->setActive(false);
}

// update the animations
void Medication::update()
{
	m_pressButton->update();
}

// set the new player positions, used for collision checking
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
			m_pressButton->setActive(true);

			m_meds.at(i).m_inBounds = true;
		}
		else
		{
			m_meds.at(i).m_inBounds = false;
		}
	}
	if (!inMeds)
	{
		m_pressButton->setActive(false);
	}
}

// check if the player picked up an item
bool Medication::checkInteract()
{
	for (unsigned int i = 0; i < m_meds.size(); i++)
	{
		if (m_meds.at(i).m_inBounds)
		{
			DEBUG_MSG("picked up item");
			m_meds.at(i).uninitialise();
			return true;
		}
	}
	return false;
}
