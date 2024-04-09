#pragma once

#include "AbstractState.h"

enum class State
{
	None, PlayerInput
};



class NoneState : public AbstractState
{
public:
	virtual void enter(std::shared_ptr<Pawn> t_pawn);
	virtual void update(std::shared_ptr<Pawn> t_pawn);
	virtual void exit(std::shared_ptr<Pawn> t_pawn);
};

class playerInputState : public AbstractState
{
public:
	virtual void enter(std::shared_ptr<Pawn> t_pawn);
	virtual void update(std::shared_ptr<Pawn> t_pawn);
	virtual void exit(std::shared_ptr<Pawn> t_pawn);
};

class StateManager
{
public:
	static void changeCommand(State t_newState, std::shared_ptr<Pawn> t_pawn);
	static void update(std::shared_ptr<Pawn> t_pawn);
};

