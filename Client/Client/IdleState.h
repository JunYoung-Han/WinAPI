#pragma once
#include "State.h"

class CIdleState : public CState
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CIdleState();
	~CIdleState();
};