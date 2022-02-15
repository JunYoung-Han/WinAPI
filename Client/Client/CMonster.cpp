#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CMissile2.h"
#include "CScene.h"
#include "CSceneMgr.h"



CMonster::CMonster()
	: m_vCenterPos(0, 0)
	, m_fSpeed(200.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_fAcc(0)
	, m_bMissileType(true)
{
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
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

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);
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
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);
}
