#include "pch.h"
#include "CCore.h"
#include "CObject.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����.
	RECT rt = { 0, 0, m_ptResolution.x , m_ptResolution.y };
	// ������ �ػ󵵿� �׵θ�, �޴����� ũ�⸦ �����Ͽ� �ٽ� rt�� ��ȯ
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	// �������� ��ġ�� ũ�⸦ �������ִ� �Լ�
	SetWindowPos(m_hWnd, nullptr, 300, 300, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	return S_OK;
}


void CCore::progress()
{
	// 1�ʿ� ���μ��� �Լ��� ���� Ƚ�� üũ
	static int callcount = 0;
	++callcount;
	static int iCount = 0;
	static int iPrev = GetTickCount();
	if (GetTickCount() - iPrev > 1000)
	{
		iPrev = GetTickCount();
		callcount = 0;
	}

	update();

	render();
}

#define MOVEPIX	2
void CCore::update()
{
	// ���������� Ȯ���ϴ� ��.

	// �񵿱� Ű ����� �Լ�.
	// => �� �ڵ尡 ����Ǵ� ���� üũ��. (��׶��忩�� �׻� �����.)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	// ���� �̼����� �� Ȯ���ϰ� ���� �� 0x8000 �� ���� ��Ʈ Ȯ���ϸ� ��.
	{
		g_obj.m_ptPos.x -= MOVEPIX;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	// ���� �̼����� �� Ȯ���ϰ� ���� �� 0x8000 �� ���� ��Ʈ Ȯ���ϸ� ��.
	{
		g_obj.m_ptPos.x += MOVEPIX;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)	// ���� �̼����� �� Ȯ���ϰ� ���� �� 0x8000 �� ���� ��Ʈ Ȯ���ϸ� ��.
	{
		g_obj.m_ptPos.y -= MOVEPIX;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	// ���� �̼����� �� Ȯ���ϰ� ���� �� 0x8000 �� ���� ��Ʈ Ȯ���ϸ� ��.
	{
		g_obj.m_ptPos.y += MOVEPIX;
	}

}

void CCore::render()
{
	// ���� �׸��� ��.
	Rectangle(m_hDC
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
