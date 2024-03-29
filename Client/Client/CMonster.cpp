#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CMissile2.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CCollider.h"



CMonster::CMonster()
	: m_pAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}
void CMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}
void CMonster::update()
{
	m_pAI->update();
#if 0
	Vec2 vCurPos = GetPos();

	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// 배회 거리 기준량을 넘어갔는지 확인.
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		// 방향 변경 - 초과한 만큼(fDist)을 움직여준다.
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	m_fAcc += fDT;

	if (1.f < m_fAcc)
	{
		if (m_bMissileType)
		{
			// CreateMissile();
			m_bMissileType = false;
		}
		else
		{
			// CreateMissile2();
			m_bMissileType = true;
		}
		m_fAcc = 0;
	}

	SetPos(vCurPos);
#endif // 0

}


void CMonster::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(false);
	pMissile->SetSpeed(200.f);



	// 이벤트 등록형식으로 바꿀 예정.
	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);
}

void CMonster::CreateMissile2()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	// Missile Object
	CMissile2* pMissile = new CMissile2;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetCenterPos(vMissilePos);
	pMissile->SetDir(false);
	pMissile->SetSpeed(200.f);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		//m_tInfo.fHP -= 1.f;
		//if (0 >= m_tInfo.fHP)
		//{
		//	DeleteObject(this);
		//}

	}
}

void CMonster::OnCollision(CCollider* _pOther)
{

}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
	CreateMissile2();
}
