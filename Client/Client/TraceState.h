#pragma once
#include "State.h"

class CTraceState : public CState
{
private:

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CTraceState();
	~CTraceState();
};

