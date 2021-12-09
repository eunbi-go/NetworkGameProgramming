#include "stdafx.h"
#include "Leaf2.h"
//#include "BmpManager.h"
#include "ObjManager.h"
//#include "KeyManager.h"
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
}

void CLeaf2::Release()
{
}
