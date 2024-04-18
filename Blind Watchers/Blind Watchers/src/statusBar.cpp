#include "statusBar.h"
#include "Game.h"

// return if the bar is empty or not
bool bar::checkEmpty()
{
    if (FillType::Empty == type)
    {
        if (fillPercent <= 0.f)
        {
            return true;
        }
    }
    else if(FillType::FillUp == type)
    {
        if (fillPercent >= 1.f)
        {
            return true;
        }
    }
    return false;
}

// apply modifications
void bar::update()
{
    //float newPercent = 1.0f * ((top->getScale().x / top->getScale().x) / fillPercent);
    //top->setScale(fillPercent, 1.f);

    // fillPercent = mods->update();
}

/// <summary>
/// change how much of the bar is filled in
/// </summary>
/// <param name="t_change">how much the bar should increase / decrease by</param>
void bar::changePercent(float t_change)
{
    if (FillType::Empty == type)
    {
        fillPercent -= t_change;
    }
    else if (FillType::FillUp == type)
    {
        fillPercent += t_change;
    }

    top->setScale(fillPercent, 1.f);
}

void bar::setPercent(float t_newPercent)
{
    fillPercent = t_newPercent;
    top->setScale(fillPercent, 1.f);
}

float continuous::update()
{
    return Game::deltaTime * m_percent;
}

/// <summary>
/// spawn a new bar that will work as declared
/// </summary>
/// <param name="t_barType">fill up, or empty</param>
/// <param name="t_newBar">data such as size and position</param>
/// <param name="t_startPercent">from 0.0f to 1.0f</param>
/// <returns></returns>
std::shared_ptr<bar> StatusBar::addNewBar(FillType t_barType, barData t_newBar, sf::Color t_fillColor, float t_startPercent)
{
    if (t_startPercent < 0.f)
    {
        if (t_barType == FillType::FillUp)
        {
            t_startPercent = 0.f;
        }
        if (t_barType == FillType::Empty)
        {
            t_startPercent = 1.f;
        }
    }

    std::shared_ptr<bar> newBar;
    newBar = std::make_shared<bar>();

    newBar->fillPercent = t_startPercent;

    newBar->type = t_barType;
    newBar->bottom = std::make_shared<sf::RectangleShape>();
    newBar->bottom->setFillColor(sf::Color(255, 255, 255, 60));
    newBar->bottom->setPosition(t_newBar.position);
    newBar->bottom->setSize(t_newBar.size);

    newBar->top = std::make_shared<sf::RectangleShape>();
    newBar->top->setFillColor(t_fillColor);
    newBar->top->setPosition(t_newBar.position);
    newBar->top->setSize(t_newBar.size);
    newBar->top->setScale(1.f, t_startPercent);

    RenderObject::getInstance().addHUD(newBar->bottom);
    RenderObject::getInstance().addHUD(newBar->top);

    return newBar;
}
