#pragma once

// ★ 싱글톤 패턴 ★
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능
// 객체 선언을 방지해야함
/*
class CCore
{
private:
	static CCore* g_pInst;

	// CCore 자기 스스로를 만들어주는 함수를 제공.
	// CCore 클래스를 만들서 그 객체를 반환해주는 함수 제공.
	// 문제점. 멤버함수를 통해 객체를 만드려면, 객체가 있어야 멤버함수를 호출가능.
	// => like 달걀 or 닭 who's first?
	// 다행히 객체가 없어도 되는 멤버함수가 있다.
	// => static 키워드 정적 멤버함수 (클래스에 종속) --> 객체없이 호출 가능.

public:
CCore* CCore::GetInstance()
{
	// 최초 호출 된 경우
	// 함수가 종료되더라도 유지되는 메모리 (정적 변수)
	// 정적변수의 초기화는 한번만 수행된다.
	if (nullptr == g_pInst)
	{
		g_pInst = new CCore;
	}

	return g_pInst;
}



	// 객체 없이 호출가능한 delete
void CCore::Release()
{
	if (nullptr != g_pInst)
	{
		delete g_pInst;
		g_pInst = nullptr;
	}
}

private:
	// 외부에서 객체 생성을 막도록.
	CCore();
	~CCore();
};
*/

// Data 영역에 객체 생성하기
class CCore
{
	
	// 정적멤버로 인스턴스를 얻어옴. -> 객체 없이 호출해서 받아와야해서.
	// 동적할당으로 객체 생성하는 방법보다 훨씬 간단하다.
	// 관리자급 클래스로 쓸때 많이 쓰는 방식. (리소스를 불러오는 방식)
	// => 자주 쓰니 매크로 함수로 만들자!
	/*
	static CCore* GetInst()
	{
		// static --> data 메모리 영역 사용.
		static CCore core;

		return &core;
	}
	*/
	// 매크로를 사용하면 이렇게 가능.
	SINGLE(CCore);

private:
	HWND	m_hWnd;	// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 메인 윈도후 해상도
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