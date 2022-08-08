#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// ★★★ idea 굳!!
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,// LEFT,
	VK_RIGHT,// RIGHT,
	VK_UP,// UP,
	VK_DOWN,// DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,

	// LAST,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	// Vector의 상태값 초기화 
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기.
	// 메인 윈도우.
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	// 프로그램이 보유한 윈도우 (아무것도 포커싱 아니면 nullptr)
	HWND hWnd = GetFocus(); // 현재 포커스 된 윈도우 값을 알려준다.

	if (nullptr != hWnd)
	{


		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}

			// 키가 안눌려있다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}
		// Mouse 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos); // 우리 윈도우 기준으로 했을 때 좌표


		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}
	// 윈도우 포커싱 해제상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}