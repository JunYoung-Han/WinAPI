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
	// Object 추가.
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));

	// 부모에서 protected로 선언해서 받아오는 밑의 방식 대신
	// m_arrObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj);
	// 부모에 함수 만들어서 사용.
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	RegisterPlayer(pObj);

	// Monster Object 추가.
	// 몬스터 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonster = CMonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMonster, GROUP_TYPE::MONSTER); // GameObject List 가 되겠지. 아니면 Layer_Monster 정도.

	// 충돌 지정
	// Player 그룹과 Monster 그룹간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look 지정
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

// Start 씬 빠져나갈 때.
void CScene_Start::Exit()
{
	
	CCollisionMgr::GetInst()->ResetGroup();
}

