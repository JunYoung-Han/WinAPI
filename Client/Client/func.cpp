#include "pch.h"

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
