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

	// 각도 성분으로 표현.
	// vPos.x += m_fSpeed * fDT * cosf(m_fTheta);
	// vPos.y -= m_fSpeed * fDT * sinf(m_fTheta);

	// 길이 성분으로 표현.
	// 이렇게 하면 x와 y의 비율값으로 값을 넣을 수 있다.
	// x,y의 비율을 유지한 대각이 1일 때의 x 크기.
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
	// 컴포넌트 (충돌체, etc..) 가 있는 경우 렌더링
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
