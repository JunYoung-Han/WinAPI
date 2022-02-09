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
			// �١١١١� ��¦ ���ؾȰ��µ�..? �١١١١�
			// => m_arrObj[i] �׷� ������ j ��ü ����.
			// ���Ͱ� END �ε��� ���� �ִ°� �ƴ϶�, ���͸� END(32)�� ��ŭ ������ ����.
			delete m_arrObj[i][j];

			// m_arrObj[i][j] = nullptr;
			// ==> vector �Ҹ��ڿ��� �Ҹ��ϱ� ������ nullptr ��ä���൵ �ȴ�.
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
