#include "pch.h"

void ChageAIState(AI* _pAI, MON_STATE _eNextState)
{

	// 이벤트 방식으로 AI 상태를 바꿔준다.
#if 0
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;			// 이벤트를 신청하는 AI
	evn.wParam = (DWORD_PTR)_eNextState;	// 신청하는 상태.

	CEvenMgt::GetInst()->AddEvent(evn);
#endif // 0

}
