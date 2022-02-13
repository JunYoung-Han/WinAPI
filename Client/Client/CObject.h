#pragma once

// : 화면에 존재하는 물체 하나하나
// : 추상 클래스

class CObject
{

	/*
	public:
		POINT m_ptPos;
		POINT m_ptScale;*/

private:
	Vec2	m_vPos;
	Vec2	m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	virtual void update() = 0;
	virtual void render(HDC _dc);

public:
	CObject();
	virtual ~CObject();	// 부모 객체의 포인터로 자식을 접근하기 때문에 자식의 소멸자에 접근하려면 부모소멸자를 가상함수로 선언.

};

