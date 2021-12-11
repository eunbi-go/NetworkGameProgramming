#include "stdafx.h"
#include "MaxPotion.h"
//#include "BmpManager.h"

CMaxPotion::CMaxPotion()
{
}


CMaxPotion::~CMaxPotion()
{
	Release();
}

void CMaxPotion::Initialize()
{
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 1000;
}

int CMaxPotion::Update()
{
	if (m_tInfo.bisDead)
		return OBJ_DEAD;

	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CMaxPotion::Late_Update()
{
}

void CMaxPotion::Render(HDC _DC)
{
}

void CMaxPotion::Release()
{
}
