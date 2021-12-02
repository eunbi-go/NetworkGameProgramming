#include "stdafx.h"
#include "Rock1.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "TileManager.h"

Rock1::Rock1()
{
}


Rock1::~Rock1()
{
	Release();
}

void Rock1::Initialize()
{
	m_eBlock = MAPBLOCK::ROCK1;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;
}

int Rock1::Update()
{
	Update_Rect();
	return OBJ_NOEVENET;
}

void Rock1::Late_Update()
{
}

void Rock1::Render(HDC _DC)
{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Rock1");
		m_tRect.top + 10;
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0, 0,
			50, 50,
			RGB(64, 168, 27));

		if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
			Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Rock1::Release()
{
}
