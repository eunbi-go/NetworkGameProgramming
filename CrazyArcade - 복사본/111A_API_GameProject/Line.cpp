#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LINEPOS & _Left, LINEPOS & _Right)
	: m_tInfo(_Left, _Right)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_tInfo.tLeftPos.fX, (int)m_tInfo.tLeftPos.fY, nullptr);
	LineTo(_DC, (int)m_tInfo.tRightPos.fX, (int)m_tInfo.tRightPos.fY);
}
