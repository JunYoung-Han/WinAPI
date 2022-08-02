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

// bit 값이 true면 해당 행그룹과 열그룹의 충돌을 검사한다.
void CCollisionMgr::update()
{
	// 행
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// 열
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			// 각 행의 열자리가 ON되어있는지 확인
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
	// 현재씬에서 iRow와 iCol에 있는 물체들의 정보를 가져와야함.
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체 없으면 검사할 필요 X
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 충돌체 없으면 검사할 필요 X or 자기 자신과 충돌 검사할 필요 X
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디 생성.
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			ID.ID; // 두 충돌체로만 나올수 있는 값이 나오게 된다. -> 맵의 key값으로 쓰겠다.

			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록('충돌하지 않았다' 로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// 이제 제대로 충돌 검사 해보자.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중이다.

				if (iter->second)
				{
					// 이전에도 충돌 하고 있었다.

					// 충돌 중인 상태인데 한놈이라도 이번 프레임 마지막에 삭제당할 녀석이면,
					// 충돌 벗어나는 처리로 해줘야함.
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
					// 이전에는 충돌하지 않았다.(충돌 진입)

					// 하필 충돌되는 타이밍에 한놈이라도 프레임 마지막에 삭제당하는 녀석이면,
					// 그냥 충돌을 안한 셈 쳐줘 
					// == 둘다 살아있을 녀석인 경우에만 OnCollisionEnter 해줘
					if (!vecLeft[i]->IsDead() && !vecRight[i]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			// 현재 충돌하고 있지 않다.
			else
			{
				// 이전에는 충돌 하고 있었다.
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
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용.


	UINT iRow = (UINT)_eLeft;	// 행
	UINT iCol = (UINT)_eRight;	// 열

	// 열이 더 커야한다. -> 대칭쪽에
	// 행,열 31, ~, 0
	// 0
	// ~
	// 31
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // 이미 Check 되어있다면,
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // Bit 빼기.
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // bit 넣기.
	}
}
