#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}
CCollisionMgr::~CCollisionMgr()
{
}

// bit ���� true�� �ش� ��׷�� ���׷��� �浹�� �˻��Ѵ�.
void CCollisionMgr::update()
{
	// ��
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// ��
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			// �� ���� ���ڸ��� ON�Ǿ��ִ��� Ȯ��
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	// ��������� iRow�� iCol�� �ִ� ��ü���� ������ �����;���.
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü ������ �˻��� �ʿ� X
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü ������ �˻��� �ʿ� X or �ڱ� �ڽŰ� �浹 �˻��� �ʿ� X
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����.
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			ID.ID; // �� �浹ü�θ� ���ü� �ִ� ���� ������ �ȴ�. -> ���� key������ ���ڴ�.

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �� ��� ������ ��� ���('�浹���� �ʾҴ�' ��)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// ���� ����� �浹 �˻� �غ���.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�.

				if (iter->second)
				{
					// �������� �浹 �ϰ� �־���.

					// �浹 ���� �����ε� �ѳ��̶� �̹� ������ �������� �������� �༮�̸�,
					// �浹 ����� ó���� �������.
					if (vecLeft[i]->IsDead() || vecRight[i]->IsDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
 						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					// �������� �浹���� �ʾҴ�.(�浹 ����)

					// ���� �浹�Ǵ� Ÿ�ֿ̹� �ѳ��̶� ������ �������� �������ϴ� �༮�̸�,
					// �׳� �浹�� ���� �� ���� 
					// == �Ѵ� ������� �༮�� ��쿡�� OnCollisionEnter ����
					if (!vecLeft[i]->IsDead() && !vecRight[i]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			// ���� �浹�ϰ� ���� �ʴ�.
			else
			{
				// �������� �浹 �ϰ� �־���.
				if (iter->second)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}

		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{

	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	float fDiff_X = abs(vRightPos.x - vLeftPos.x);
	float fScale_X = (vLeftScale.x + vRightScale.x) * 0.5;

	float fDiff_Y = abs(vRightPos.y - vLeftPos.y);
	float fScale_Y = (vLeftScale.y + vRightScale.y) * 0.5;

	if ((fDiff_X < fScale_X) && (fDiff_Y < fScale_Y))
	{
		return true;
	}
#if 0
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}
#endif // 0


	return false;
}




void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���.


	UINT iRow = (UINT)_eLeft;	// ��
	UINT iCol = (UINT)_eRight;	// ��

	// ���� �� Ŀ���Ѵ�. -> ��Ī�ʿ�
	// ��,�� 31, ~, 0
	// 0
	// ~
	// 31
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // �̹� Check �Ǿ��ִٸ�,
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // Bit ����.
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // bit �ֱ�.
	}
}
