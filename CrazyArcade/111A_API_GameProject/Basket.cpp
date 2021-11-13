#include "stdafx.h"
#include "Basket.h"
#include "BmpManager.h"
#include "ObjManager.h"
#include "TileManager.h"
#include "KeyManager.h"


CBasket::CBasket()
{
}


CBasket::~CBasket()
{
	Release();
}


void CBasket::Initialize()
{
	m_eState = OBJSTATE::IDLE;
	m_eBlock = MAPBLOCK::BASKET;


	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 200;
}

int CBasket::Update()
{
	
	if (m_eState == OBJSTATE::BUBBLE)
	{
		CTileManager::Get_Instance()->SetTileBlockType(m_tInfo.fX, m_tInfo.fY, MAPBLOCK::NOBLOCK);
		return OBJ_DEAD;

	}
	if (m_eState == OBJSTATE::DEAD)
	{

	}


	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CBasket::Late_Update()
{
}

void CBasket::Render(HDC _DC)
{
	HDC hMemDC;
	switch (m_eState)
	{
	case OBJSTATE::IDLE:
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Basket");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0, 0,
			50, 50,
			RGB(64, 168, 27));
		break;
	case OBJSTATE::BUBBLE:
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BasketPop");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			m_tFrame.iFrameStart * 40, 0,
			50, 50,
			RGB(64, 168, 27));
		break;

	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBasket::Release()
{
}
