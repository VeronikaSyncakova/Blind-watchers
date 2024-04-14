#include "statusBar.h"
#include "Game.h"

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

void bar::update()
{
    fillPercent = mods->update();
}

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

float continuous::update()
{
    return Game::deltaTime * m_percent;
}

std::shared_ptr<bar> StatusBar::addNewBar(FillType t_barType, barData t_newBar, float t_startPercent)
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
    newBar->top->setFillColor(sf::Color(255, 0, 0, 100));
    newBar->top->setPosition(t_newBar.position);
    newBar->top->setSize(t_newBar.size);
    newBar->top->setScale(1.f, t_startPercent);

    RenderObject::getInstance().addHUD(newBar->bottom);
    RenderObject::getInstance().addHUD(newBar->top);

    return newBar;
}
