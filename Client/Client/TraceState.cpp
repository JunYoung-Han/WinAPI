#include "pch.h"
#include "TraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CTimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	// Ÿ���� �� Player�� �i�ư���.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos = vMonPos + vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();
	// ���� �������� �̻� �Ǹ� �ٽ� Idle�� ��������.
	if (fLen > GetMonster()->GetInfo().fRecogRange)
	{
		m_pAI->ChangeState(MON_STATE::IDLE);
	}
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
