#pragma once
// '충돌' 이라는 기능을 구현한 컴포넌트.
// Object에 붙어서 활성/비활성화 가능

// Object의 영역을 검사할 것이다.


class CObject;

class CCollider
{
private:
	// 정적 클래스 변수 -> 클래스 밖에서 초기화
	static UINT g_iNextID;

	CObject* m_pOwner;		// collider를 소유하고 있는 오브젝트
	Vec2	m_vOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vec2	m_vFinalPos;	// finalupdate 에서 매 프레임마다 계산
	Vec2	m_vScale;		// 충돌체의 크기

	UINT	m_iID;			// 충돌체 고유한 ID 값 (~42억개)
	UINT	m_iCol;			// 충돌 된 객체들 갯수 세기 용

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// 충돌 상태 경우의 수 처리 함수.
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수.
	void OnCollisionEnter(CCollider* _pOther); // 충돌 진입시.
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제시.


	// ★ 이런것도 되네?!?!?!?!?!?!?!?!?
	// CColiider a, b;  a = b  가 되는 것을 방지.
	// Collider 끼리 대입이 되지 않도록 하기 위해.
	// 대입연산자 없앤것과 같다.
	CCollider& operator = (CCollider& _origin) = delete;


public:
	CCollider();
	// 각각의 객체들은 id가 달라야함.
	// -> 깊은 복사를 해주어야 한다.
	CCollider(const CCollider& _origin);
	~CCollider();

	
	friend class CObject;

};

