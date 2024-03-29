#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "SelectGDI.h"
#include "resource.h"
#include "EventMgr.h"

#include "Camera.h"


// CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	DestroyMenu(m_hMenu);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	// 해상도에 맞게 윈도우 크기 조정.
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// 메뉴바 생성. -> FSM(3) 강의에서 함.
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));


	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	// m_hDC와 호환성 가지는 비트맵 생성
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	// m_hDC와 호환성 가지는 DC 생성
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	// 기본으로 나오는 1픽셀 제거.
	DeleteObject(hOldBit);
	// 자주 사용할 펜 및 브러쉬 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	// g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	// g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}


void CCore::progress()
{
	// =============
	// Manager Update
	// =============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();



	// =============
	// Scene Update 
	// =============
	CSceneMgr::GetInst()->update();

	// 충돌 체크.
	CCollisionMgr::GetInst()->update();



	// =============
	// Rendering 
	// =============
	// 화면 Clear
	Clear();

	CSceneMgr::GetInst()->render(m_memDC);

	// 비트맵 복사 함수
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();


	// =============
	// 이벤트 지연 처리. 
	// =============
	// 한 프레임 랜더링 끝나고 마지막에 처리되면 다음번 프레임에 적용된다.
	// (생성, 소멸, SCENE_CHANGE 등등)
	CEventMgr::GetInst()->update();

}

void CCore::Clear()
{
	SelectGDI gdi(m_memDC, BRUSH_TYPE::BLACK);
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	// 함수 종료시점에 소멸자에서 gdi 다시 초기화 해줌.
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

// 툴씬에서는 메뉴바 생성해주기 때문에 만든 함수.
void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	// 해상도에 맞게 윈도우 크기 조정.
	RECT rt = { (LONG)0, (LONG)0, (LONG)_vResolution.x , (LONG)_vResolution.y };
	// 지정된 해상도에 테두리, 메뉴바의 크기를 포함하여 다시 rt에 반환
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // 메뉴바 없는걸로 계산.
	// 윈도우의 위치와 크기를 조정해주는 함수
	SetWindowPos(m_hWnd, nullptr, 300, 300, rt.right - rt.left, rt.bottom - rt.top, 0);

}


#if 0
void CCore::update() //1 프레임
{
	Vec2 vPos = g_obj.GetPos();
	// 변경점들을 확인하는 곳.

	// 비동기 키 입출력 함수.
	// => 이 코드가 수행되는 순간 체크함. (백그라운드여도 항상 실행됨.)
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)	// 지금 이순간의 값 확인하고 싶은 때 0x8000 젤 상위 비트 확인하면 됨.
	{
		vPos.x -= 500.f * fDT; // 프레임 당 걸린시간마다 여기 탐.;
		// ★ 즉!!!! 컴터 사양 관계 없이,  (누른시간)걸린 시간 만큼! 가게 된다.!!!
		// ★ 즉!!!!!!!!!!!!!! ★★★ 1초당 1픽셀!!!! ★★★★
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 500.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		vPos.y -= 500.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		vPos.y += 500.f * fDT;
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	// 실제 그리는 곳.
	Rectangle(m_memDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	// 비트맵 복사 함수
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}
#endif
