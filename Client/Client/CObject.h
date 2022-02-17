#pragma once

// : 화면에 존재하는 물체 하나하나
// : 추상 클래스

class CCollider;


class CObject
{

	/*
	public:
		POINT m_ptPos;
		POINT m_ptScale;*/

private:
	Vec2			m_vPos;
	Vec2			m_vScale;

	// 필요하면 필요한 Object에서 자체적으로 동적할당 하면 됨.
	// nullptr면 해당객체는 충돌체가 필요 X 는거.
	CCollider*		m_pCollider;

	

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void update() = 0;

	// 가상함수로 안둠 --> 자식이 오버라이딩 해도 부모쪽만 호출 된다.
	// ==> final 키워드로 오버라이딩 금지시킬 수 있다.
	virtual void finalupdate() final;	// 오버라이딩 막음.
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();	// 부모 객체의 포인터로 자식을 접근하기 때문에 자식의 소멸자에 접근하려면 부모소멸자를 가상함수로 선언.

};

