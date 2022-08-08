#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
	
private:
	Vec2		m_vLookAt; // ī�޶� ���� ��ġ
	CObject*	m_pTargetObj;	// ī�޶� Ÿ�� ������Ʈ.

	Vec2		m_vDiff; // �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

public:
	void update();

private:
	void CalDiff();

};