#include "stdafx.h"
#include "LineManager.h"
#include "Line.h"

CLineManager* CLineManager::m_pInstance = nullptr;

CLineManager::CLineManager()
{
}


CLineManager::~CLineManager()
{
	Release();
}

void CLineManager::Initialize()
{
	LINEPOS tTemp[4] = { {0.f, 700.f}, {1000.f, 700.f}, {300.f, 600.f}, {700.f, 600.f} };
	m_ListLine.emplace_back(new CLine(tTemp[0], tTemp[1]));
	m_ListLine.emplace_back(new CLine(tTemp[2], tTemp[3]));
}

void CLineManager::Render(HDC _DC)
{
	for (auto& pLine : m_ListLine)
		pLine->Render(_DC);
}

void CLineManager::Release()
{
	for_each(m_ListLine.begin(), m_ListLine.end(), Safe_Delete<CLine*>);
	m_ListLine.clear();
}

bool CLineManager::CollisionLine(float _x, float* _y)
{
	if (m_ListLine.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& pLine : m_ListLine)
	{
		if (pLine->Get_Info().tLeftPos.fX < _x
			&& pLine->Get_Info().tRightPos.fX > _x)
			pTarget = pLine;
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Info().tLeftPos.fX;
	float y1 = pTarget->Get_Info().tLeftPos.fY;
	float x2 = pTarget->Get_Info().tRightPos.fX;
	float y2 = pTarget->Get_Info().tRightPos.fY;

	*_y = (y2 - y1) / (x2 - x1) * (_x - x1) + y1;

	return true;
}
