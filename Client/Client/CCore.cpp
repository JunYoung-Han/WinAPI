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

	// 해상도에 맞게 윈도우 크기 조정.
	RECT rt = { 0, 0, m_ptResolution.x , m_ptResolution.y };
	// 지정된 해상도에 테두리, 메뉴바의 크기를 포함하여 다시 rt에 반환
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	// 윈도우의 위치와 크기를 조정해주는 함수
	SetWindowPos(m_hWnd, nullptr, 300, 300, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	return S_OK;
}


void CCore::progress()
{
	// 1초에 프로세스 함수의 실행 횟수 체크
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
	// 변경점들을 확인하는 곳.

	// 비동기 키 입출력 함수.
	// => 이 코드가 수행되는 순간 체크함. (백그라운드여도 항상 실행됨.)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		g_obj.m_ptPos.x -= MOVEPIX;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		g_obj.m_ptPos.x += MOVEPIX;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		g_obj.m_ptPos.y -= MOVEPIX;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		g_obj.m_ptPos.y += MOVEPIX;
	}

}

void CCore::render()
{
	// 실제 그리는 곳.
	Rectangle(m_hDC
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
