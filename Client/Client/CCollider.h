#pragma once
// '�浹' �̶�� ����� ������ ������Ʈ.
// Object�� �پ Ȱ��/��Ȱ��ȭ ����

// Object�� ������ �˻��� ���̴�.


class CObject;

class CCollider
{
private:
	// ���� Ŭ���� ���� -> Ŭ���� �ۿ��� �ʱ�ȭ
	static UINT g_iNextID;

	CObject* m_pOwner;		// collider�� �����ϰ� �ִ� ������Ʈ
	Vec2	m_vOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vec2	m_vFinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	Vec2	m_vScale;		// �浹ü�� ũ��

	UINT	m_iID;			// �浹ü ������ ID �� (~42�ﰳ)
	UINT	m_iCol;			// �浹 �� ��ü�� ���� ���� ��

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
	// �浹 ���� ����� �� ó�� �Լ�.
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�.
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���Խ�.
	void OnCollisionExit(CCollider* _pOther); // �浹 ������.


	// �� �̷��͵� �ǳ�?!?!?!?!?!?!?!?!?
	// CColiider a, b;  a = b  �� �Ǵ� ���� ����.
	// Collider ���� ������ ���� �ʵ��� �ϱ� ����.
	// ���Կ����� ���ذͰ� ����.
	CCollider& operator = (CCollider& _origin) = delete;


public:
	CCollider();
	// ������ ��ü���� id�� �޶����.
	// -> ���� ���縦 ���־�� �Ѵ�.
	CCollider(const CCollider& _origin);
	~CCollider();

	
	friend class CObject;

};

