#include "pch.h"
#include "EventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::update()
{
	// =================================================
	// 이전 프레임에서 등록해준 Dead Object 들을 삭제한다.
	// =================================================
	for (auto& iterDeadObj : m_vecDead)
	{
		delete iterDeadObj;
	}
	m_vecDead.clear();

	// ===========
	// Event 처리
	// ===========
	for (auto& iterEvent : m_vecEvent)
	{
		ExcuteEvent(iterEvent);
	}
	m_vecEvent.clear();
}

void CEventMgr::ExcuteEvent(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObject = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		// 이걸 해주면 다음 프레임 부터 pNewObject의 update 함수가 실행된다.
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObject, eType);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object를 Dead 상태로 변경.
		// 삭제 예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();			// Obj를 비활성화 해주고 
		m_vecDead.push_back(pDeadObj);	// 쓰레기통에 넣어준다.
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
	}
	break;
	}
}
