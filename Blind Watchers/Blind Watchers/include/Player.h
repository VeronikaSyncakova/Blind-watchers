#pragma once

#include "Pawn.h"
#include "Camera.h"

class Player : public Pawn
{
public:
	Player();
	~Player();

	void update()override;

	void expire()override;

	void moveBody(sf::Vector2f const& t_moveVector)override;
	virtual sf::FloatRect getBounds()override { return m_body->getGlobalBounds(); }
	void rotate(float t_angle)override;

	void position(sf::Vector2f& t_position) override;
	void writeYAML(YAML::Emitter& t_out) override;
private:
	std::shared_ptr<sf::RectangleShape> m_body;

	CameraTracker m_followCam;

	bool m_sprinting{ false };
	float m_sprintTimeLeft{ 2.f };
	float m_maxSprintTime{ 2.f };
	float m_sprintSpeed{ 200.f };
};
