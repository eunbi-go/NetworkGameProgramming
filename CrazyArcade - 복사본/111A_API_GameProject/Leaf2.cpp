#include "stdafx.h"
#include "Leaf2.h"
#include "BmpManager.h"
#include "ObjManager.h"
#include "KeyManager.h"
#include "TileManager.h"

CLeaf2::CLeaf2()
{
}


CLeaf2::~CLeaf2()
{
	Release();
}

void CLeaf2::Initialize()
{
	m_eState = OBJSTATE::IDLE;
	m_eBlock = MAPBLOCK::LEAF2;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_eState = OBJSTATE::IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 200;
}

int CLeaf2::Update()
{
	if (m_eState == OBJSTATE::BUBBLE)
	{
		CTileManager::Get_Instance()->SetTileBlockType(m_tInfo.fX, m_tInfo.fY, MAPBLOCK::NOBLOCK);
		return OBJ_DEAD;
	}


	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CLeaf2::Late_Update()
{
}

void CLeaf2::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Leaf2");
	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY, hMemDC,
		0, 0,
		50, 50,
		RGB(64, 168, 27));

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLeaf2::Release()
{
}
