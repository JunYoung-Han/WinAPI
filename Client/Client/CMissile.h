#pragma once
#include "CObject.h"

// CMissile
// : Scene 에다가 미리 배치시키는 것이 아님.

class CMissile :
	public CObject
{
private:
	float	m_fDir; // 위 아래 방향
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