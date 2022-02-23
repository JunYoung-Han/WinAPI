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

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void finalupdate();
	void render(HDC _dc);


public:
	CCollider();
	~CCollider();

	
	friend class CObject;

};

