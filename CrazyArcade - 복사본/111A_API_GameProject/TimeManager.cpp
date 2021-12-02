#include "stdafx.h"
#include "TimeManager.h"

CTimeManager* CTimeManager::m_pInstance = nullptr;


CTimeManager::CTimeManager()
{
}


CTimeManager::~CTimeManager()
{
}

HRESULT CTimeManager::Ready_CTimeManager()
{
	m_dDeltaTime = 0.0;

	QueryPerformanceFrequency(&m_CpuTick);

	QueryPerformanceCounter(&m_PreTime);
	QueryPerformanceCounter(&m_CurTime);

	return S_OK;
}

void CTimeManager::Update_CTimeManager()
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_CurTime);

	m_dDeltaTime = double(m_CurTime.QuadPart - m_PreTime.QuadPart) / m_CpuTick.QuadPart;

	m_PreTime = m_CurTime;
}
