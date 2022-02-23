#pragma once
// �� ���� ������Ʈ���� ����
// �� �ȿ� ����Ʈ �׷�, ����, �÷��̾� ��� �ִ°�.

// ���漱�� ���� : ������� ���θ� �����ϴ� �� �����ϰ���.
class CObject;	// �����ϼӵ��� ������ ���� �ʱ� ����.
// ����� �����ϸ�, ������Ʈ �ڵ尡 ����� �� ���� ���� �Ź� ������ Ȯ�� ��.
// �׷��� ���� ������Ʈ�� ���� ���ϰ� �׳� �̷� �갡 �ִٴ� ������ �Ѿ�Ա� ������
// ������Ʈ�� ����Ǵ��� ������ �����Ϸ��� ��Ȯ������ �ʴ´�.


class CScene
{
	//protected:	// �θ� ��� ������ protected �� �ϸ� ����� �������. �������� �ڽĵ��� �� ���� �� �� ���ڳ�.
					// --> �� �� ������ protected �Լ��� �����ϰ� �����.
private:
	// CObject a; // ���漱�� -> Ŭ���� Ÿ�� ��ü�� �� �� ����.
	// ����Ÿ������ ��ü���� ������ ���. // ���߿� ��ũ�� �ѱ�
	// --> ������ Ÿ�Ը� ��밡��

	// Cobject�� ������ �Ļ��� ������Ʈ Ŭ�������� ���� �θ� Ÿ��
	// �ڽ� ������ Ÿ���� �̰ɷ� �� ���� �� �ִ�.
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName; // Scene �̸�

// protected:
public:
	// ����� �Լ� �����Ͽ� inlineȭ
	void AddObject(CObject* _Obj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_Obj);
	}
	// ������ �ٷ��� ������ �ش�.
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	// �۾��� ������. -ex) �浹ü�� �÷��̾ ���󰡰� �ϴ� ��.
	void finalupdate();
	void render(HDC _dc);


	// �ش� Scene ���Խ� ȣ��
	virtual void Enter() = 0; // ���� ���� �Լ�
	// --> ���� ���� �Լ��� ������ �ִ� Ŭ������ �߻� Ŭ������ �ȴ�.
	// ==> ���� ��ü ������ �Ұ��� ������.
	// ==> �����ؾ� �� �Լ�(Enter()�� �ݵ�� �����ض�!)�� �˸��� ����.

	// �ش� Scene ��� �� ȣ��
	virtual void Exit() = 0;

public:
	CScene();
	virtual ~CScene();	// �ڽ����� �Ҹ��ڸ� ȣ���ϱ� ���� �θ��� CScene�� �����Լ��� ����.
						// �θ� ��ü�� �����ͷ� �ڽ��� �����ϱ� ������ �ڽ��� �Ҹ��ڿ� �����Ϸ��� �θ�Ҹ��ڸ� �����Լ��� ����.
};

