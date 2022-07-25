// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;	// 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// 지역
// 전역
// 정적 ( 데이터 영역 )
// 1. 함수 안에
// 2. 파일 
// 3. 클래스 안에

// SAL 주석언어 : _In_ 함축된 의미로 약속된 키워드를 달아두는 것.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 프로세서가 메모리에 올라갈 때 시작되는 시작주소.
// 가상메모리 시스템이 들어오기 이전에는 실제적 전체 메모리중에 자기 위치의 메모리주소를 받았었다.
// 즉, 가상메모리를 사용하는 지금은 쓸모없는 인자이다.
_In_opt_ HINSTANCE hPrevInstance,
// 프로그램을 윈도우 명령 프롬프트로 실행할 때, 추가적인 인자로 문자열을 넣어줄 수 있다.
_In_ LPWSTR    lpCmdLine,
_In_ int       nCmdShow)
{
	// 메모리 릭(누수) 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(215); //  문제 발생시, 해당 지점 중단점 걸어줌.



	// 윈도우는 각 프로그램마다 고유한 자신만의 영역이 있음. RAM
	// 실제 물리적으로는 다른 메모리 공간이 할당.
	// 사용자에게 보여지는 주소는 마치 이 세상에 자신이 혼자만 있는 것처럼 느끼게
	// 가상으로 잡아줌!!!! RAM 의 가상 메모리이다.

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	// 윈도우 정보 등록
	MyRegisterClass(hInstance);

	// 윈도우 생성.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Core 초기화
	// GetInst로 바로 객체 만들고, 그 객체의 초기화 함수 호출함.
	if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280, 768 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

		return FALSE;
	}




	// 단축키 테이블 정보 로딩
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;


	// 기본 메시지 루프입니다
	// 메시지 받음.
	// 주요 특징 : 메시지큐에서 메시지 확일 될 떄 까지 대기. (내부에서 대기 함)(안되면 while이 끝날 수도 있음)
	// msg.message == WM_QUIT  이 발생할 경우. false 반환. --> 프로그램 종료
	// 메시지 반응형태의 프로그램 구조임 --> 게임으로는 비효율적 --> 기본 구조를 고칠 예정
	//while (GetMessage(&msg, nullptr, 0, 0))

	// PeekMessage
	// 메시지의 유무와 관계없이 반환
	// 메시지큐에서 메시지를 확인한 경우 true, 메시지큐에 메시지가 없는 경우 false를 반환한다.

	while (true)
	{
		// 메시지 있으면 true, 없으면 false
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		// 메시지가 발생하지 않는 대부분의 시간.
		else
		{
			//메시지가 없는 동안 호출.
			// Game 코드 수행
			// 디자인 패턴(설계 유형)
			// 싱글톤 패턴
			CCore::GetInst()->progress();
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT);
	wcex.lpszClassName = L"Key";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindowW(L"Key", L"MyGame", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// WPARAM wParam, LPARAM lParam 은 해당 message의 부가인자값.(부연설명)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:  // 무효화 영역(Invalidate)이 발생한 경우
		// case 안에 괄호 : 지역변수 선언 시 필요.
	{
		PAINTSTRUCT ps;
		// hWnd: 현재 윈도우 handler ID
		HDC hdc = BeginPaint(hWnd, &ps);    //Device Context (그리기)


		// 윈도우 핸들
		// HDC -> Device Context objext의 id값을 받는 Handler

		// ★ Device Context ★
		// 그리기 작업을 수행하는데 필요한 데이터 집합체
		// (펜, 브러쉬, 
		// 해당 DC가 목적지로 하고있는 그림판에 그 DC 안에 펜 정보로 그림을 그리겠다.
		// DC 의 목적지는 hWnd
		// DC 의 브러쉬는 기본 브러쉬(White)

		// 직접 펜과 브러쉬를 만들어서 DC에 적용
		HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

		// 기본 펜과 브러쉬 ID 값을 받아 둠
		HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); //=> 굉장히 범용적인 함수.
		HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush); //=> 굉장히 범용적인 함수.

		// 변경된 펜과 브러쉬로 사각형 그림

		/*
			Rectangle(hdc
				, 1180, 668
				, 1280, 768); // 내부는 white 브러쉬로 채워짐.
		*/


		// DC 의 펜과 브러쉬를 원래 것으로 되돌림
		SelectObject(hdc, hDefaultPen);
		SelectObject(hdc, hDefaultBrush);

		// 다 쓴 펜, 브러쉬 삭제 요청
		DeleteObject(hRedPen);
		DeleteObject(hBlueBrush);

		// 그리기 종료
		EndPaint(hWnd, &ps);
	}
	break;
	// 해당 윈도우가 포커싱 된 상태에서 키보드 키가 눌리면 발생.
	case WM_KEYDOWN:
	{
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	}
	break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_LBUTTONUP:
		break;

		//  SetTimer() 함수 사용시, 설정 주기에 따라다음 case 에 걸림.
	case WM_TIMER:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
