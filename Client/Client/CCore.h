#pragma once

// �� �̱��� ���� ��
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����
// ��ü ������ �����ؾ���
/*
class CCore
{
private:
	static CCore* g_pInst;

	// CCore �ڱ� �����θ� ������ִ� �Լ��� ����.
	// CCore Ŭ������ ���鼭 �� ��ü�� ��ȯ���ִ� �Լ� ����.
	// ������. ����Լ��� ���� ��ü�� �������, ��ü�� �־�� ����Լ��� ȣ�Ⱑ��.
	// => like �ް� or �� who's first?
	// ������ ��ü�� ��� �Ǵ� ����Լ��� �ִ�.
	// => static Ű���� ���� ����Լ� (Ŭ������ ����) --> ��ü���� ȣ�� ����.

public:
CCore* CCore::GetInstance()
{
	// ���� ȣ�� �� ���
	// �Լ��� ����Ǵ��� �����Ǵ� �޸� (���� ����)
	// ���������� �ʱ�ȭ�� �ѹ��� ����ȴ�.
	if (nullptr == g_pInst)
	{
		g_pInst = new CCore;
	}

	return g_pInst;
}



	// ��ü ���� ȣ�Ⱑ���� delete
void CCore::Release()
{
	if (nullptr != g_pInst)
	{
		delete g_pInst;
		g_pInst = nullptr;
	}
}

private:
	// �ܺο��� ��ü ������ ������.
	CCore();
	~CCore();
};
*/

// Data ������ ��ü �����ϱ�
class CCore
{
	
	// ��������� �ν��Ͻ��� ����. -> ��ü ���� ȣ���ؼ� �޾ƿ;��ؼ�.
	// �����Ҵ����� ��ü �����ϴ� ������� �ξ� �����ϴ�.
	// �����ڱ� Ŭ������ ���� ���� ���� ���. (���ҽ��� �ҷ����� ���)
	// => ���� ���� ��ũ�� �Լ��� ������!
	/*
	static CCore* GetInst()
	{
		// static --> data �޸� ���� ���.
		static CCore core;

		return &core;
	}
	*/
	// ��ũ�θ� ����ϸ� �̷��� ����.
	SINGLE(CCore);

private:
	HWND	m_hWnd;	// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};