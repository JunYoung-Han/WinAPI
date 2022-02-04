

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double			m_dDT; // 프레임 사이의 시간 값 (1프레임당 시간값)
	double			m_dAcc;	// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// update() 호출 횟수 체크
	UINT			m_iFPS;	// 초당 호출 횟수
	// FPS
	// 1 프레임당 시간(s) delta time

public:
	void init();
	void update();

public:
	double GetDt() { return m_dDT; }
	float GetfDt() { return (float)m_dDT; }

};