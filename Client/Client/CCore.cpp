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


	// �ػ󵵿� �°� ������ ũ�� ����.
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// �޴��� ����. -> FSM(3) ���ǿ��� ��.
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));


	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	// m_hDC�� ȣȯ�� ������ ��Ʈ�� ����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	// m_hDC�� ȣȯ�� ������ DC ����
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	// �⺻���� ������ 1�ȼ� ����.
	DeleteObject(hOldBit);
	// ���� ����� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
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



	// =============
	// Scene Update 
	// =============
	CSceneMgr::GetInst()->update();

	// �浹 üũ.
	CCollisionMgr::GetInst()->update();



	// =============
	// Rendering 
	// =============
	// ȭ�� Clear
	Clear();

	CSceneMgr::GetInst()->render(m_memDC);

	// ��Ʈ�� ���� �Լ�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();


	// =============
	// �̺�Ʈ ���� ó��. 
	// =============
	// �� ������ ������ ������ �������� ó���Ǹ� ������ �����ӿ� ����ȴ�.
	// (����, �Ҹ�, SCENE_CHANGE ���)
	CEventMgr::GetInst()->update();

}

void CCore::Clear()
{
	SelectGDI gdi(m_memDC, BRUSH_TYPE::BLACK);
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	// �Լ� ��������� �Ҹ��ڿ��� gdi �ٽ� �ʱ�ȭ ����.
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

// ���������� �޴��� �������ֱ� ������ ���� �Լ�.
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
	// �ػ󵵿� �°� ������ ũ�� ����.
	RECT rt = { (LONG)0, (LONG)0, (LONG)_vResolution.x , (LONG)_vResolution.y };
	// ������ �ػ󵵿� �׵θ�, �޴����� ũ�⸦ �����Ͽ� �ٽ� rt�� ��ȯ
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // �޴��� ���°ɷ� ���.
	// �������� ��ġ�� ũ�⸦ �������ִ� �Լ�
	SetWindowPos(m_hWnd, nullptr, 300, 300, rt.right - rt.left, rt.bottom - rt.top, 0);

}


#if 0
void CCore::update() //1 ������
{
	Vec2 vPos = g_obj.GetPos();
	// ���������� Ȯ���ϴ� ��.

	// �񵿱� Ű ����� �Լ�.
	// => �� �ڵ尡 ����Ǵ� ���� üũ��. (��׶��忩�� �׻� �����.)
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)	// ���� �̼����� �� Ȯ���ϰ� ���� �� 0x8000 �� ���� ��Ʈ Ȯ���ϸ� ��.
	{
		vPos.x -= 500.f * fDT; // ������ �� �ɸ��ð����� ���� Ž.;
		// �� ��!!!! ���� ��� ���� ����,  (�����ð�)�ɸ� �ð� ��ŭ! ���� �ȴ�.!!!
		// �� ��!!!!!!!!!!!!!! �ڡڡ� 1�ʴ� 1�ȼ�!!!! �ڡڡڡ�
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
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// �׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	// ���� �׸��� ��.
	Rectangle(m_memDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	// ��Ʈ�� ���� �Լ�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}
#endif
