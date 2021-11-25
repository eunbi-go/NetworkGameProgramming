#include "stdafx.h"
#include "Obj.h"

CObj::CObj()
	: m_dwTime(GetTickCount()), m_eBlock(MAPBLOCK::NOBLOCK), m_ePreDir(OBJDIR::END), m_eCurDir(OBJDIR::END), m_eState(OBJSTATE::END)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}

CObj::~CObj()
{
}
