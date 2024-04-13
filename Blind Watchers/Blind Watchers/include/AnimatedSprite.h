#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Drawable
{
public:
	AnimatedSprite(float waitTime, sf::Texture texture) : 
		m_texture(texture), m_waitTimeBetweenFrames(waitTime), m_currentFrameTime(waitTime)
	{
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}
	void setOrigin(sf::Vector2f t_origin)
	{
		m_sprite.setOrigin(t_origin);
	}
	void setPosition(sf::Vector2f t_newPosition)
	{
		m_sprite.setPosition(t_newPosition);
	}
	void addFrame(sf::IntRect t_newFrame)
	{
		m_renderRegions.push_back(t_newFrame);
	}
	void update();
	void setActive(bool active) { m_active = active; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		if(m_active)
			target.draw(m_sprite, states);
	}
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_renderRegions;
	int m_selectedRegion{ 0 };
	float m_waitTimeBetweenFrames{ 1.f };
	float m_currentFrameTime{ 1.f };

	bool m_active{ true };
};

#endif // !ANIMATED_SPRITE_H
