#pragma once

class CObject;
class AI;

void ChageAIState(AI* _pAI, MON_STATE _eNectState);

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{

	}
}

// 이벤트 매니저에 전달해주기 위한 함수.
// 사실 객체에 직접 구현해도 되는데, 자주 사용되는 루틴이니 편의를 위해.
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup); // 생성 함수.
void DeleteObject(CObject* _pObj);