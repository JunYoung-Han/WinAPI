#pragma once
#include "State.h"


//
// 1. �� ���Ͱ� �����ϰ� �ִ� �پ��� ������Ʈ�� ��ȯ�� �� �ְ� �ϴ� ����
// 2. ������� ���� �ൿ ������ ������ �� �ƴ�.
// 3. �پ��� ���͵��� ������Ʈ�� ������ �� �ֵ���.
// 
//

class CMonster;

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


public:
	AI();
	~AI();
};
