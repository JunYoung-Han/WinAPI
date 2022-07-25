#include "pch.h"
#include "IdleState.h"

// 자식클래스는 부모의 기본 생성자 호출
// 부모의 기본 생성자가 없으므로 전달해주기.
CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
