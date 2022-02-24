#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	// 두 값의 비트가 합쳐지는걸 이용해서 고유한 값을 만드는거라니..신기합니다!
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	// 충돌체 간의 이전 프레임 충돌 정보
	// 이전 정보를 알려면 두 충돌체만의 키값으로 저장된 이전충돌 정보가 있어야함.
	map<ULONGLONG, bool> m_mapColInfo;

	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 매트릭스
public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};