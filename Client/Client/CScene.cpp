#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// ☆☆☆☆☆ 살짝 이해안가는데..? ☆☆☆☆☆
			// => m_arrObj[i] 그룹 벡터의 j 물체 삭제.
			// 벡터가 END 인덱스 까지 있는게 아니라, 벡터를 END(32)개 만큼 생성한 상태.
			delete m_arrObj[i][j];

			// m_arrObj[i][j] = nullptr;
			// ==> vector 소멸자에서 소멸하기 때문에 nullptr 안채워줘도 된다.
		}
	}
}


void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}
