#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object 추가.
	CObject* pObj = new CObject;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));

	// 부모에서 protected로 선언해서 받아오는 밑의 방식 대신
	// m_arrObj[(UINT)GROUP_TYPE::DEFAULT].push_back(pObj);
	// 부모에 함수 만들어서 사용.
	AddObject(pObj, GROUP_TYPE::DEFAULT);

}

void CScene_Start::Exit()
{
	
}

