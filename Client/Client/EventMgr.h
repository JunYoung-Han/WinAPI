#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;	//64bit ü������ 8 ����Ʈ.
	DWORD_PTR	wParam; // �Ķ���ͷ� ���� �� ���� 8����Ʈ �ּ� Ÿ���� ���� �ֱ⿡.
};

class CEventMgr
{
	SINGLE(CEventMgr)

private:
	vector<tEvent>		m_vecEvent;
	vector<CObject*>	m_vecDead; // ���� ������ ������Ʈ�� ��Ƶδ� ��������.

public:
	void update();

private:
	void ExcuteEvent(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

