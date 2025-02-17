#include "RenderObject.h"
#include "SettingsStorage.h"
#include "simpleMaths.h"

RenderObject::RenderObject() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "Epsilon" }
{
	loadsettings();

	// set the screen to the standard 1920x1080
	m_cameraView = sf::View(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_hudView = sf::View(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_window.setView(m_cameraView);
}


////////////////////////////////////////////////
///
///	 adding of new object to the drawable array
/// 
////////////////////////////////////////////////
void RenderObject::appendToObject(std::vector<std::weak_ptr<sf::Drawable>>& t_obj, std::shared_ptr<sf::Drawable> t_new)
{
	for (unsigned int i = 0; i < t_obj.size(); i++)
	{
		if (t_obj.at(i).lock() == nullptr) // if the object is empty
		{
			t_obj.at(i) = t_new;
			return;
		}
	}

	t_obj.push_back(t_new);
}

void RenderObject::updateCamera(sf::Vector2f t_move)
{
	m_cameraView.move(t_move);
	m_window.setView(m_cameraView);
}

void RenderObject::setCamera(sf::Vector2f t_newPosition)
{
	m_cameraView.setCenter(t_newPosition);
	m_window.setView(m_cameraView);
}


void RenderObject::zoomCamera(float t_zoom, sf::Vector2f& t_centerPoint)
{
	sf::Vector2f currentCenter = m_cameraView.getCenter();
	if (!math::circleIntersects(t_centerPoint, currentCenter,1.f,1.f))
	{
		sf::Vector2f centeringVec = math::displacement(m_cameraView.getCenter(), t_centerPoint);
		centeringVec *= 100.f;
		m_cameraView.setCenter(currentCenter.x+centeringVec.x,currentCenter.y+centeringVec.y);
	}
	
	//m_cameraView.setCenter(t_centerPoint);
	m_cameraView.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT)* t_zoom);
	//m_cameraView.zoom(t_zoom);
}
void RenderObject::centerView(float t_zoom, sf::Vector2f& t_centerPoint)
{
	m_cameraView.setCenter(t_centerPoint);
	m_cameraView.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT) * t_zoom);
}
void RenderObject::loadsettings()
{
	SettingsStorage::getInstance().initSettings();
	SettingsData& data = SettingsStorage::getInstance().getSettings();

	m_window.setSize(sf::Vector2u(data.ScreenSize.x, data.ScreenSize.y)); // set the screen size from the yaml file here
	m_window.setVerticalSyncEnabled(data.vsync);
}
void RenderObject::add(std::shared_ptr<sf::Drawable> t_new) { appendToObject(m_assets, t_new); }
void RenderObject::addHUD(std::shared_ptr<sf::Drawable> t_new) { appendToObject(m_hud, t_new); }
void RenderObject::addBG(std::shared_ptr<sf::Drawable> t_new) { appendToObject(m_backGround, t_new); }
void RenderObject::addParticles(std::shared_ptr<sf::Drawable> t_new) { appendToObject(m_particles, t_new); }
////////////////////////////////////////////////




////////////////////////////////////////////////
///
///	 Clear the drawing arrays
/// 
////////////////////////////////////////////////
void RenderObject::clear()
{
	m_backGround.clear();
	m_assets.clear();
	m_hud.clear();
	m_particles.clear();
}
////////////////////////////////////////////////




////////////////////////////////////////////////
///
///	 Render the layers
/// 
////////////////////////////////////////////////
void RenderObject::render()
{
	m_window.clear();
	m_window.setView(m_cameraView);
	for (unsigned int i = 0; i < m_backGround.size(); i++)
		if (m_backGround.at(i).lock() != nullptr)
			m_window.draw(*m_backGround.at(i).lock());

	for (unsigned int i = 0; i < m_particles.size(); i++)
		if (m_particles.at(i).lock() != nullptr)
			m_window.draw(*m_particles.at(i).lock());

	for (unsigned int i = 0; i < m_assets.size(); i++)
		if (m_assets.at(i).lock() != nullptr)
			m_window.draw(*m_assets.at(i).lock());

	m_window.setView(m_hudView);
	for (unsigned int i = 0; i < m_hud.size(); i++)
		if (m_hud.at(i).lock() != nullptr)
			m_window.draw(*m_hud.at(i).lock());

	m_window.display();
}
////////////////////////////////////////////////
