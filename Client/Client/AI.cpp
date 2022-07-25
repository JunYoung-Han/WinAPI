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
	// �̹� �����ϴ��� Ȯ�� 
	CState* pState = FindState(_pState->GetType());
	assert(!pState); // ������Ʈ �� ����.
	// ���� AI�� �ʿ� ������Ʈ ����.
	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	// State���Դ� ���� AI �� �˷���.
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
	// ����ó��.
	assert(m_pCurState != pNextState); // �����Ȳ�� �־��ش�.

	m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}