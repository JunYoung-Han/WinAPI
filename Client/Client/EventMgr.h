#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;	//64bit 체제에선 8 바이트.
	DWORD_PTR	wParam; // 파라미터로 전달 할 값이 8파이트 주소 타입일 수도 있기에.
};

class CEventMgr
{
	SINGLE(CEventMgr)

private:
	vector<tEvent>		m_vecEvent;
	vector<CObject*>	m_vecDead; // 삭제 예정인 오브젝트들 모아두는 쓰레기통.

public:
	void update();

private:
	void ExcuteEvent(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

