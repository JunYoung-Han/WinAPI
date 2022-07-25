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