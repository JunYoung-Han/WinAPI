#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fSpeed(600.f)
	, m_fTheta(0)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize();
	CreateCollider();
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	// 각도 성분으로 표현.
	// vPos.x += m_fSpeed * fDT * cosf(m_fTheta);
	// vPos.y -= m_fSpeed * fDT * sinf(m_fTheta);

	// 길이 성분으로 표현.
	// 이렇게 하면 x와 y의 비율값으로 값을 넣을 수 있다.
	// x,y의 비율을 유지한 대각이 1일 때의 x 크기.
	vPos.x += m_fSpeed * fDT * m_vDir.x;
	vPos.y += m_fSpeed * fDT * m_vDir.y;


	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}