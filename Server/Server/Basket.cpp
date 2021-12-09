#include "stdafx.h"
#include "Basket.h"
//#include "BmpManager.h"
#include "ObjManager.h"
#include "TileManager.h"
//#include "KeyManager.h"


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
}

void CBasket::Release()
{
}
