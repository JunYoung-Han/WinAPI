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

CPlayer::CPlayer()
	: m_bMissileType(true)
	, m_pTex(nullptr)
{
	// Texture �ε�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"jy", L"texture\\jy64.bmp");
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
	// �Է½ÿ� ������ �� �� �־. (ȭ�� �� �Ѿ ��)
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

	// Ư�� ���� ���� �ؼ� BitBlt ���ִ� �Լ�
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
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
// ����
// 1. �÷��̾� �̻��� ���� �߰� (OK)
// 2. ���͵� �̻��� ���� �߰� (OK)
// 3. �̻����� ȭ�� �ۿ� ������ �����ֱ�.
