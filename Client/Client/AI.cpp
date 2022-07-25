#include "pch.h"
#include "AI.h"
#include "State.h"

AI::AI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

AI::~AI()
{
	//Safe_Delete_Map(m_mapState);
}

void AI::update()
{
	m_pCurState->update();
}

void AI::finalupdate()
{
}

void AI::AddState(CState* _pState)
{
	// 이미 존재하는지 확인 
	CState* pState = FindState(_pState->GetType());
	assert(!pState); // 널포인트 면 문제.
	// 현재 AI의 맵에 스테이트 저장.
	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	// State에게는 현재 AI 를 알려줌.
	_pState->m_pAI = this;
}

CState* AI::FindState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;
	return iter->second;
}

void AI::SetCurState(MON_STATE _eState)
{
	m_pCurState = FindState(_eState);
	assert(m_pCurState);
}

void AI::ChangeState(MON_STATE _eNextState)
{
	CState* pNextState = FindState(_eNextState);
	// 예외처리.
	assert(m_pCurState != pNextState); // 정상상황을 넣어준다.

	m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}