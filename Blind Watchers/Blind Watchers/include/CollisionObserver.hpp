#pragma once

#include "Observer.h"

struct Bullet;

class npcCollisionObserver : public ObserverTemplate
{
public:
    virtual void listen(Bullet& t_bullet) = 0;
};
