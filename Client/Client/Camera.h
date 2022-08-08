#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
	
private:
	Vec2		m_vLookAt;		// 카메라가 볼 지정 위치(지금 지정된 곳)
	Vec2		m_vCurLookAt;	// 이전 위치와 현재위치 보정 위치.
	Vec2		m_vPrevLookAt;	// 카메라가 보는 이전프레임 위치

	CObject*	m_pTargetObj;	// 카메라 타겟 오브젝트.

	Vec2		m_vDiff; // 해상도 중심위치와, 카메라 LookAt 간의 차이값

	float		m_fTime; // 타겟을 따라가는데 걸리는 
	float		m_fSpeed;
	float		m_fAccTime;

public:
	//void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetLookAt(Vec2 _vLook) 
	{
#if 1
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
#endif // 0
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; };
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; };

public:
	void update();

private:
	void CalDiff();

};