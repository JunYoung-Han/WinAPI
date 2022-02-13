#pragma once
#include "CObject.h"

// CMissile
// : Scene ���ٰ� �̸� ��ġ��Ű�� ���� �ƴ�.

class CMissile :
	public CObject
{
private:
	float	m_fDir; // �� �Ʒ� ����
	float	m_fSpeed;

public:
	void SetDir(bool _bUp)
	{
		if (_bUp)
			m_fDir = -1.f;
		else
			m_fDir = 1.f;
	}

public:
	void SetSpeed(float _f) { m_fSpeed = _f; }

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CMissile();
	~CMissile();
};