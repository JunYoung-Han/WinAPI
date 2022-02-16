#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"

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

	{
		// Monster Object 추가.
		// 몬스터 배치
		int iMonCount = 10;
		float fMoveDist = 25.f;
		float fObjScale = 50.f;
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

		CMonster* pMonsterObj = nullptr;
		for (int i = 0; i < iMonCount; ++i)
		{
			// Monster Object 추가.
			// : 다운캐스팅 해야하니 부모(CObject)가 아닌 자식(CMonster) 객체 생성
			pMonsterObj = new CMonster;
			pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (fTerm * (float)i), 50.f));
			pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
			pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
			pMonsterObj->SetMaxDistance(fMoveDist);
			AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
		}
	}

}

void CScene_Start::Exit()
{

}

