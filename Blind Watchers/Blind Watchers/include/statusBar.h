#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <SFML/Graphics.hpp>

struct barData
{
	sf::Vector2f position;
	sf::Vector2f size;
};

enum class FillType
{
	FillUp, Empty
};

class barModifiers
{
public:
	virtual float update() = 0;
};

class continuous : public barModifiers
{
public:
	continuous(float t_percentPerSecond)
	{
		m_percent = t_percentPerSecond;
	}
	float update()override;
private:
	float m_percent{ 0.f };
};

struct bar
{
	bool checkEmpty();
	void update();
	void changePercent(float t_change);
	std::shared_ptr<sf::RectangleShape> top;
	std::shared_ptr<sf::RectangleShape> bottom;

	float fillPercent{ 0.f };
	FillType type;
	std::shared_ptr<barModifiers> mods;
};

class StatusBar
{
public:
	static std::shared_ptr<bar> addNewBar(FillType t_barType, barData t_newBar, float t_startPercent = -1.f);
	//static void update();
};

#endif // !STATUS_BAR_H