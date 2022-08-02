#include "pch.h"
#include "func.h"

#include "EventMgr.h"

void ChageAIState(AI* _pAI, MON_STATE _eNextState)
{

	// �̺�Ʈ ������� AI ���¸� �ٲ��ش�.
#if 0
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;			// �̺�Ʈ�� ��û�ϴ� AI
	evn.wParam = (DWORD_PTR)_eNextState;	// ��û�ϴ� ����.

	CEvenMgt::GetInst()->AddEvent(evn);
#endif // 0

}

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}
