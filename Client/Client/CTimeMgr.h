

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double			m_dDT; // ������ ������ �ð� �� (1�����Ӵ� �ð���)
	double			m_dAcc;	// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	// update() ȣ�� Ƚ�� üũ
	UINT			m_iFPS;	// �ʴ� ȣ�� Ƚ��
	// FPS
	// 1 �����Ӵ� �ð�(s) delta time

public:
	void init();
	void update();
	void render();

public:
	double GetDt() { return m_dDT; }
	float GetfDt() { return (float)m_dDT; }

};