#include "pch.h"
#include "MonsterFactory.h"
#include "CMonster.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

/*
* 이런식으로 Factory 클래스를 사용하면 장점.
* 몬스터 개인 클래스 마다 일일히 안잡고 여기서 관리하면 된다.
* 몬스터 각각의 특정 상태 함수만 정의하면 되지 않을까?
*/


										// 몬스터 종류에 따라 다르게 생성.
CMonster* CMonsterFactory::CreateMonster(MONSTER_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMonster = nullptr;

	switch (_eType)
	{
	case MONSTER_TYPE::NORMAL: // 다람쥐 몬스터 일 경우.
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

		AI* pAI = new AI; // 그때 결정되는 상태 초기화
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
