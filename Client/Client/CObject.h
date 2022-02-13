#pragma once

// : ȭ�鿡 �����ϴ� ��ü �ϳ��ϳ�
// : �߻� Ŭ����

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
	virtual ~CObject();	// �θ� ��ü�� �����ͷ� �ڽ��� �����ϱ� ������ �ڽ��� �Ҹ��ڿ� �����Ϸ��� �θ�Ҹ��ڸ� �����Լ��� ����.

};

