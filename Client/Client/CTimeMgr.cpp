#include "pch.h"
#include "CTimeMgr.h"
#include "framework.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{
}
CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// 현재 클럭 수
	QueryPerformanceCounter(&m_llPrevCount);
	// 1 초당 클럭 수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// 한 프레임 동안의 클럭 차이를 알 수 있다.
	// 내가 원하는 것: 한 프레임에 걸린 시간 값.
	// => 1프레임당 클럭 수 / 1초당 클럭수 == 프레임당 클럭수 * (1클럭당 시간) =
	// => 프레임당 걸린 시간
	// => (Clock/Frame) 
	//   ---------------
	//    (Clock/Second)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// 이전 카운트 값을 현재값으로 갱신 (다음번 계산을 위해)
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;	// DT 누적.

	// 1초 세기.
	if (1. <= m_dAcc)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,   DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
