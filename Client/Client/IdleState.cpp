#include "pch.h"
#include "IdleState.h"

// �ڽ�Ŭ������ �θ��� �⺻ ������ ȣ��
// �θ��� �⺻ �����ڰ� �����Ƿ� �������ֱ�.
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
