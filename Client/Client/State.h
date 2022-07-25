#pragma once
//class AI;

class CState
{
private:
	class AI* m_pAI;
	MON_STATE	m_eState;

public:
	class AI* GetAI() { return m_pAI; }


public:
	virtual void update()	PURE;
	virtual void Enter()	PURE;
	virtual void Exit()		PURE;


public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;

};

