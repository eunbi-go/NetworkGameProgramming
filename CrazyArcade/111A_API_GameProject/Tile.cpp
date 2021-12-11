#include "stdafx.h"
#include "Tile.h"
#include "BmpManager.h"

CTile::CTile()
	: m_iTilekey(0)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;
}

int CTile::Update()
{
	return OBJ_NOEVENET;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _DC)
{
	Update_Rect();
	if (m_iTilekey == 1)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile1");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 2)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile2");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 3)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile3");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 4)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile4");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 5)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile5");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 6)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile6");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 7)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile7");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 8)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile8");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 9)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile9");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_iTilekey == 10)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile10");
		BitBlt(_DC, m_tRect.left, m_tRect.top
			, TILECX, TILECY, hMemDC, 0, 0, SRCCOPY);
	}

}

void CTile::Release()
{
}
