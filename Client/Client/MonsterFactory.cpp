#include "pch.h"
#include "MonsterFactory.h"
#include "CMonster.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

/*
* �̷������� Factory Ŭ������ ����ϸ� ����.
* ���� ���� Ŭ���� ���� ������ ����� ���⼭ �����ϸ� �ȴ�.
* ���� ������ Ư�� ���� �Լ��� �����ϸ� ���� ������?
*/


										// ���� ������ ���� �ٸ��� ����.
CMonster* CMonsterFactory::CreateMonster(MONSTER_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMonster = nullptr;

	switch (_eType)
	{
	case MONSTER_TYPE::NORMAL: // �ٶ��� ���� �� ���.
	{
		pMonster = new CMonster;
		pMonster->SetPos(_vPos);

		tMonsterInfo info = {};
		info.fAttackPower = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 10.f;
		info.fSpeed = 150.f;

		pMonster->SetMonsterInfo(info);
		pMonster->SetName(L"Monster");

		AI* pAI = new AI; // �׶� �����Ǵ� ���� �ʱ�ȭ
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMonster->SetAI(pAI);
	}
	break;
	case MONSTER_TYPE::RANGE:
		break;
	}

	assert(pMonster);
	return pMonster;
}
