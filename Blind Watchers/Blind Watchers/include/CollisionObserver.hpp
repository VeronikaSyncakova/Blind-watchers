#pragma once

#include "Observer.h"

struct collisionInfo;

class npcCollisionObserver : public ObserverTemplate
{
public:
    virtual void listen(collisionInfo& t_bullet) = 0;
};
