#include "stdafx.h"
#include "Potion.h"
#include "BmpManager.h"

CPotion::CPotion()
{
}


CPotion::~CPotion()
{
	Release();
}

void CPotion::Initialize()
{
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 1000;
}

int CPotion::Update()
{
	if (m_tInfo.bisDead)
		return OBJ_DEAD;

	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CPotion::Late_Update()
{
}

void CPotion::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Potion");
	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY, hMemDC,
		m_tFrame.iFrameStart * 50, 0,
		50, 62,
		RGB(64, 168, 27));
}

void CPotion::Release()
{
}
