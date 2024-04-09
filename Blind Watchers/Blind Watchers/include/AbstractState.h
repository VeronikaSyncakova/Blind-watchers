#pragma once

#include <iostream>

class AbstractState;
class Pawn;

class AbstractState
{
public:
	virtual void enter(std::shared_ptr<Pawn> t_pawn) = 0;
	virtual void update(std::shared_ptr<Pawn> t_pawn) = 0;
	virtual void exit(std::shared_ptr<Pawn> t_pawn) = 0;
};