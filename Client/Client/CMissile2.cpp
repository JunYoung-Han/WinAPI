#include "pch.h"
#include "CMissile2.h"
#include "CTimeMgr.h"

void CMissile2::update()
{
	Vec2 vPos = GetPos();

	vPos.y += m_fSpeed * fDT * m_fDirY;

	vPos.x += 300.f * fDT * m_fDirX;
	float fDist = abs(m_vCenterPos.x - vPos.x) - m_fMaxDistanceX;
	if (0.f < fDist)
	{
		m_fDirX *= -1;
		vPos.x += fDist * m_fDirX;
	}

	SetPos(vPos);
}

void CMissile2::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	Ellipse(_dc, (int)(vRenderPos.x - vScale.x / 2.f), (int)(vRenderPos.y - vScale.y / 2.f)
		, (int)(vRenderPos.x + vScale.x / 2.f), (int)(vRenderPos.y + vScale.y / 2.f));
}

CMissile2::CMissile2()
	: m_fDirY(1.f)
	, m_fDirX(1.f)
	, m_fMaxDistanceX(40)
	, m_vCenterPos{}
	, m_fSpeed(300.f)
{
}

CMissile2::~CMissile2()
{
}
