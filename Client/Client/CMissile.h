#pragma once
#include "CObject.h"

// CMissile
// : Scene ���ٰ� �̸� ��ġ��Ű�� ���� �ƴ�.

class CMissile :
	public CObject
{
private:
	float	m_fSpeed;
	float	m_fTheta; // �̵�����

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