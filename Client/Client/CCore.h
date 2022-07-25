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

	HBITMAP	m_hBit;
	HDC		 m_memDC;

	// ���� ����ϴ� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];


	// �޴�
	HMENU	m_hMenu; // Tool Scene ������ ���.


public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

#if 0
	void update();
	void render();
#endif

public:
	const HWND	GetMainHwnd() { return m_hWnd; }
	const HDC	GetMainDC() { return m_hDC; }
	const POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; };
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; };

};