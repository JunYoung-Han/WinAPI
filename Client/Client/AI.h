#pragma once


//
// 1. 이 몬스터가 보유하고 있는 다양한 스테이트를 전환할 수 있게 하는 역할
// 2. 기능적인 몬스터 행동 패턴을 구현할 건 아님.
// 3. 다양한 몬스터들의 스테이트를 보유할 수 있도록.
// 
//

class CMonster;
class CState;

class AI
{
private:
	map<MON_STATE, CState*> m_mapState;
	CState*					m_pCurState;
	CMonster*				m_pOwner;


public:
	void update();
	void finalupdate();

public:
	void AddState(CState* _pState);
	CState* FindState(MON_STATE _eState);
	void SetCurState(MON_STATE _eState);

	void ChangeState(MON_STATE _eNextState);

	CMonster* GetOwner() { return m_pOwner; }

public:
	AI();
	~AI();

	friend class CMonster;
};
