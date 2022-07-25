#include "pch.h"
#include "IdleState.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	// 가만히 있는다.
	// Player의 위치 체크 
	CPlayer* pPlayer = (CPlayer*)(CSceneMgr::GetInst()->GetCurScene()->GetPlayer());
	Vec2 vPlayerPos = pPlayer->GetPos();

	// -> 몬스터의 범위 안에 들어오면 추적상태로 전환 (범위값은 Monster 로부터 가져온다.)
	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonsterPos;
	float fLen = vDiff.Length();

	// 플레이어가 몬스터의 인식범위 안으로 진입.
	if (fLen < pMonster->GetInfo().fRecogRange)
	{
		// AI 에게 상태 전환하라고 알려야함.
		// 이벤트 매니저 처리로 상황이 바뀌어야함.
		// 상태가 바뀌어야겠다 생각했으면, 다음번 프레임부터 적용되어야함.
		// 기본상태라 생각했는데 다른 누군가 봤을때 추적하는 것 처럼 보일 수 있음.
		// 그런가?

		// 지금은 이벤트 처리기가 없어서 이걸로 해준다.
		m_pAI->ChangeState(MON_STATE::TRACE);
	}
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
