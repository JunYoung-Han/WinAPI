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
	// ���� �����ӿ��� ������� Dead Object ���� �����Ѵ�.
	// =================================================
	for (auto& iterDeadObj : m_vecDead)
	{
		delete iterDeadObj;
	}
	m_vecDead.clear();

	// ===========
	// Event ó��
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

		// �̰� ���ָ� ���� ������ ���� pNewObject�� update �Լ��� ����ȴ�.
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObject, eType);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object�� Dead ���·� ����.
		// ���� ���� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();			// Obj�� ��Ȱ��ȭ ���ְ� 
		m_vecDead.push_back(pDeadObj);	// �������뿡 �־��ش�.
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
	}
	break;
	}
}
