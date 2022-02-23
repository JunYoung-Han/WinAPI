#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	// 충돌체 간의 이전 프레임 충돌 정보
	// 이전 정보를 알려면 두 충돌체만의 키값으로 저장된 이전충돌 정보가 있어야함.
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 매트릭스

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};