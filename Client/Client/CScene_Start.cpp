#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "IdleState.h"
#include "TraceState.h"

#include "Camera.h"
#include "CKeyMgr.h"
CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object �߰�.
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));

	// �θ𿡼� protected�� �����ؼ� �޾ƿ��� ���� ��� ���
	// m_arrObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj);
	// �θ� �Լ� ���� ���.
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	RegisterPlayer(pObj);

	// Monster Object �߰�.
	// ���� ��ġ
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonster = CMonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMonster, GROUP_TYPE::MONSTER); // GameObject List �� �ǰ���. �ƴϸ� Layer_Monster ����.

	// �浹 ����
	// Player �׷�� Monster �׷찣�� �浹 üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look ����
	Vec2 Resolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Start::update()
{
	__super::update();

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
		
	}
}

// Start �� �������� ��.
void CScene_Start::Exit()
{
	
	CCollisionMgr::GetInst()->ResetGroup();
}

