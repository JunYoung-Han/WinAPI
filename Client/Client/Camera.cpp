#include "pch.h"
#include "Camera.h"
#include "CObject.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
{

}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���.
	CalDiff();
}

void CCamera::CalDiff()
{
}