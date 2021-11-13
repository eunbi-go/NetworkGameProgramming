#include "stdafx.h"
#include "SmallMbape.h"
#include "BmpManager.h"
#include "TileManager.h"
#include "KeyManager.h"
#include "ObjManager.h"
#include "Mbape.h"

SmallMbape::SmallMbape()
{
}


SmallMbape::~SmallMbape()
{
	Release();
}

void SmallMbape::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/Small_Mbape.bmp", L"Small_Mbape");

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_tInfo.fSpeed = 1.f;

	m_eState = OBJSTATE::IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 200;
}

int SmallMbape::Update()
{
	if (m_eState == OBJSTATE::IDLE)
	{
		switch (m_eCurDir)
		{
		case OBJDIR::TOP:
			m_tInfo.fY -= (m_tInfo.fSpeed / 2);
			break;
		case OBJDIR::BOTTOM:
			m_tInfo.fY += (m_tInfo.fSpeed / 2);
			break;
		case OBJDIR::LEFT:
			m_tInfo.fX -= (m_tInfo.fSpeed / 2);
			break;
		case OBJDIR::RIGHT:
			m_tInfo.fX += (m_tInfo.fSpeed / 2);
			break;
		}

		if (m_dwTime + 7000 < GetTickCount())
		{
			CObj* pObj = CAbstractFactory<CMbape>::Create_Monster(m_tInfo.fX, m_tInfo.fY, OBJDIR::BOTTOM);
			CObjManager::Get_Instance()->Add_Object(pObj, OBJID::STRONGMONSTER);
			m_dwTime = GetTickCount();
			return OBJ_DEAD;
		}


	}

	if (m_eState == OBJSTATE::BUBBLE)
	{
		return OBJ_DEAD;
	}

	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void SmallMbape::Late_Update()
{
	if (m_eCurDir == OBJDIR::LEFT)
	{
		if (m_tInfo.fX + 1 - (TILECX >> 1) < 20 ||
			MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::BOMB == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX >> 1), m_tInfo.fY))
		{
			m_eCurDir = OBJDIR::BOTTOM;
		}
	}

	if (m_eCurDir == OBJDIR::RIGHT)
	{
		if (m_tInfo.fX + 1 + (TILECX >> 1) > 620 ||
			MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX >> 1), m_tInfo.fY) ||
			MAPBLOCK::BOMB == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX >> 1), m_tInfo.fY))
		{
			m_eCurDir = OBJDIR::TOP;
		}
	}

	if (m_eCurDir == OBJDIR::TOP)
	{
		if (m_tInfo.fY + 1 - (TILECY >> 1) < 40 ||
			MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY - (TILECY >> 1)) ||
			MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY - (TILECY >> 1)) ||
			MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY - (TILECY >> 1)) ||
			MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY - (TILECY >> 1)) ||
			MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY - (TILECY >> 1)) ||
			MAPBLOCK::BOMB == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY - (TILECY >> 1)))
		{
			m_eCurDir = OBJDIR::LEFT;
		}
	}

	if (m_eCurDir == OBJDIR::BOTTOM)
	{
		if (m_tInfo.fY + 1 + (TILECY >> 1) > 560 ||
			MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + (TILECY >> 1)) ||
			MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + (TILECY >> 1)) ||
			MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + (TILECY >> 1)) ||
			MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + (TILECY >> 1)) ||
			MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + (TILECY >> 1)) ||
			MAPBLOCK::BOMB == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + (TILECY >> 1)))
		{
			m_eCurDir = OBJDIR::RIGHT;
		}
	}
}

void SmallMbape::Render(HDC _DC)
{
	HDC hMemDC2 = CBmpManager::Get_Instance()->Find_Image(L"Small_Mbape");

	switch (m_eCurDir)
	{
	case OBJDIR::TOP:
		// 0 1
		GdiTransparentBlt(_DC, m_tRect.left - 12, m_tRect.top - 20
			, 53, 63, hMemDC2
			, 27 + m_tFrame.iFrameStart * 53, 10
			, 53, 63
			, RGB(255, 255, 255));
		break;
	case OBJDIR::BOTTOM:
		// 2 3
		GdiTransparentBlt(_DC, m_tRect.left - 12, m_tRect.top - 20
			, 53, 63, hMemDC2
			, 27 + 53 * 2 + m_tFrame.iFrameStart * 53, 10
			, 53, 63
			, RGB(255, 255, 255));
		break;
	case OBJDIR::LEFT:
		// 4 5
		GdiTransparentBlt(_DC, m_tRect.left - 12, m_tRect.top - 20
			, 69, 63, hMemDC2
			, 27 + 53 * 4 + m_tFrame.iFrameStart * 69, 10
			, 69, 63
			, RGB(255, 255, 255));
		break;
	case OBJDIR::RIGHT:
		// 6 7
		GdiTransparentBlt(_DC, m_tRect.left - 12, m_tRect.top - 20
			, 69, 63, hMemDC2
			, 29 + (53 * 4) + (69 * 2) + m_tFrame.iFrameStart * 69, 10
			, 69, 63
			, RGB(255, 255, 255));
		break;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void SmallMbape::Release()
{
}
