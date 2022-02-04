#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"


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

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2( 100, 100 ));

	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();

	render();
}

#define MOVEPIX 2
void CCore::update() //1 프레임
{
	Vec2 vPos = g_obj.GetPos();
	// 변경점들을 확인하는 곳.

	// 비동기 키 입출력 함수.
	// => 이 코드가 수행되는 순간 체크함. (백그라운드여도 항상 실행됨.)
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		vPos.x -= 1000.f * fDT; // 프레임 당 걸린시간마다 여기 탐.;
		// ★ 즉!!!! 컴터 사양 관계 없이,  (누른시간)걸린 시간 만큼! 가게 된다.!!!
		// ★ 즉!!!!!!!!!!!!!! ★★★ 1초당 1픽셀!!!! ★★★★
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		vPos.x += 1000.f * CTimeMgr::GetInst()->GetfDt();;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		vPos.y -= 1000.f * CTimeMgr::GetInst()->GetfDt();;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		vPos.y += 1000.f * CTimeMgr::GetInst()->GetfDt();;
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	// 실제 그리는 곳.
	Rectangle(m_hDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));
}
