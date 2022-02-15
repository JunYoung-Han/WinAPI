#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CMissile2.h"
#include "CSceneMgr.h"
#include "CScene.h"

void CPlayer::update()
{
	Vec2 vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 300.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 300.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 300.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 300.f * fDT;
	}
	if (KEY_TAP(KEY::B))
	{
		ChangeMissile();
	}

	if (KEY_TAP(KEY::SPACE))
	{
		if (m_bMissileType)
			CreateMissile();
		else
			CreateMissile2();
	}

	SetPos(vPos);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(2.f, -3.f));
	pMissile->SetSpeed(1000.f);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);

}
void CPlayer::CreateMissile2()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile2* pMissile = new CMissile2;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetCenterPos(vMissilePos);
	pMissile->SetDir(true);
	pMissile->SetSpeed(400.f);
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);

}

// 과제
// 1. 플레이어 미사일 종류 추가 (OK)
// 2. 몬스터도 미사일 패턴 추가 (OK)
// 3. 미사일이 화면 밖에 나가면 지워주기.
