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
	// ���� Ŭ�� ��
	QueryPerformanceCounter(&m_llPrevCount);
	// 1 �ʴ� Ŭ�� ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// �� ������ ������ Ŭ�� ���̸� �� �� �ִ�.
	// ���� ���ϴ� ��: �� �����ӿ� �ɸ� �ð� ��.
	// => 1�����Ӵ� Ŭ�� �� / 1�ʴ� Ŭ���� == �����Ӵ� Ŭ���� * (1Ŭ���� �ð�) =
	// => �����Ӵ� �ɸ� �ð�
	// => (Clock/Frame) 
	//   ---------------
	//    (Clock/Second)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���簪���� ���� (������ ����� ����)
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;	// DT ����.

	// 1�� ����.
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
