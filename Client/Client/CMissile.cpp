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

	// ���� �������� ǥ��.
	// vPos.x += m_fSpeed * fDT * cosf(m_fTheta);
	// vPos.y -= m_fSpeed * fDT * sinf(m_fTheta);

	// ���� �������� ǥ��.
	// �̷��� �ϸ� x�� y�� ���������� ���� ���� �� �ִ�.
	// x,y�� ������ ������ �밢�� 1�� ���� x ũ��.
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