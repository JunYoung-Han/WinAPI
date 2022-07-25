#pragma once
#include "CMonster.h"

class AI;

class CState
{
protected:
	class AI* m_pAI;
	MON_STATE	m_eState;

public:
	class AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }
	class CMonster* GetMonster();

public:
	virtual void update()	PURE;
	virtual void Enter()	PURE;
	virtual void Exit()		PURE;


public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;

};

