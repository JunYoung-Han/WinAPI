#include "pch.h"
#include "AI.h"


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
}