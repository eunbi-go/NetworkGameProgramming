#include "stdafx.h"
#include "Rock2.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "TileManager.h"

Rock2::Rock2()
{
}


Rock2::~Rock2()
{
	Release();
}

void Rock2::Initialize()
{
	m_eBlock = MAPBLOCK::ROCK2;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;
}

int Rock2::Update()
{
	Update_Rect();
	return OBJ_NOEVENET;
}

void Rock2::Late_Update()
{
}

void Rock2::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Rock2");
	m_tRect.top + 20;
	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY, hMemDC,
		0, 0,
		50, 50,
		RGB(64, 168, 27));

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Rock2::Release()
{
}
