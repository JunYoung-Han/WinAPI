#include "pch.h"
#include "State.h"

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}

CState::CState(MON_STATE _eState)
	: m_eState(_eState)
	, m_pAI(nullptr)
{
}

CState::~CState()
{
}
