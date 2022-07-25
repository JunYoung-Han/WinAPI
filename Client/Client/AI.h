#pragma once


//
// 1. �� ���Ͱ� �����ϰ� �ִ� �پ��� ������Ʈ�� ��ȯ�� �� �ְ� �ϴ� ����
// 2. ������� ���� �ൿ ������ ������ �� �ƴ�.
// 3. �پ��� ���͵��� ������Ʈ�� ������ �� �ֵ���.
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
