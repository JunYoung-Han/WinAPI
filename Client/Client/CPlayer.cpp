#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CMissile2.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollider.h"


CPlayer::CPlayer()
	: m_bMissileType(true)
	, m_pTex(nullptr)
{
	// Texture 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"jy", L"texture\\jy64.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(35.f, 40.f));
}

CPlayer::~CPlayer()
{
}

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

void CPlayer::render(HDC _dc)
{
	// 입력시엔 음수가 될 수 있어서. (화면 밖 넘어갈 시)
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();


	/*
	BitBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);
	*/

	// 특정 생상 제거 해서 BitBlt 해주는 함수
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	// 컴포넌트 (충돌체, etc..) 가 있는 경우 렌더링
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	pMissile->SetSpeed(400.f);

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);

	// 이벤트 처리기로 넘겨줄 예정.
	// CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	// pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_PLAYER);

}
void CPlayer::CreateMissile2()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile2* pMissile = new CMissile2;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetCenterPos(vMissilePos);
	pMissile->SetDir(true);
	pMissile->SetSpeed(400.f);
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_PLAYER);

}
// 과제
// 1. 플레이어 미사일 종류 추가 (OK)
// 2. 몬스터도 미사일 패턴 추가 (OK)
// 3. 미사일이 화면 밖에 나가면 지워주기.
