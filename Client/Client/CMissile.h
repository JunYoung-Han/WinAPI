#pragma once
#include "CObject.h"

// CMissile
// : Scene 에다가 미리 배치시키는 것이 아님.

class CMissile :
	public CObject
{
private:
	float	m_fSpeed;
	float	m_fTheta; // 이동방향

	Vec2	m_vDir;

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir; 
		m_vDir.Normalize();
	}


public:
	void SetSpeed(float _f) { m_fSpeed = _f; }

public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther) 	 override;
	virtual void OnCollision(CCollider* _pOther) 		 override;
	virtual void OnCollisionExit(CCollider* _pOther) 	 override;

public:
	CMissile();
	~CMissile();
};