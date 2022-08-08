#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fSpeed(600.f)
	, m_fTheta(0)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(15.f, 15.f));
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
	vPos = GetPos();
	if (0 >= vPos.y)
	{
		DeleteObject(this);

	}

}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	Ellipse(_dc, (int)(vRenderPos.x - vScale.x / 2.f), (int)(vRenderPos.y - vScale.y / 2.f)
		, (int)(vRenderPos.x + vScale.x / 2.f), (int)(vRenderPos.y + vScale.y / 2.f));
	// ������Ʈ (�浹ü, etc..) �� �ִ� ��� ������
	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	//if (!IsDead() && !pOtherObj->IsDead() 
	//	&& pOtherObj->GetName() == L"Monster")
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

void CMissile::OnCollision(CCollider* _pOther)
{
}

void CMissile::OnCollisionExit(CCollider* _pOther)
{
}
