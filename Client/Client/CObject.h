#pragma once

// : ȭ�鿡 �����ϴ� ��ü �ϳ��ϳ�
// : �߻� Ŭ����

class CCollider;


class CObject
{

	/*
	public:
		POINT m_ptPos;
		POINT m_ptScale;*/

private:
	wstring			m_strName;

	Vec2			m_vPos;
	Vec2			m_vScale;

	// �ʿ��ϸ� �ʿ��� Object���� ��ü������ �����Ҵ� �ϸ� ��.
	// nullptr�� �ش簴ü�� �浹ü�� �ʿ� X �°�.
	CCollider* m_pCollider;

	bool			m_bAlive; // Ȱ��ȭ ���� ���°�.


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();

	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

private:
	void SetDead() { m_bAlive = false; } // �̺�Ʈ ó���θ� ������ ���� ����.

public:
	virtual void update() = 0;

	// �����Լ��� �ȵ� --> �ڽ��� �������̵� �ص� �θ��ʸ� ȣ�� �ȴ�.
	// ==> final Ű����� �������̵� ������ų �� �ִ�.
	virtual void finalupdate() final;	// �������̵� ����.
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();	// �θ� ��ü�� �����ͷ� �ڽ��� �����ϱ� ������ �ڽ��� �Ҹ��ڿ� �����Ϸ��� �θ�Ҹ��ڸ� �����Լ��� ����.

	friend class CEventMgr;
};

