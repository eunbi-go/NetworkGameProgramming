#include "stdafx.h"
#include "Grass.h"
//#include "BmpManager.h"
#include "ObjManager.h"
//#include "KeyManager.h"
#include "TileManager.h"

CGrass::CGrass()
{
}


CGrass::~CGrass()
{
	Release();
}

void CGrass::Initialize()
{
	m_eState = OBJSTATE::IDLE;
	m_eBlock = MAPBLOCK::GRASS;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_eState = OBJSTATE::IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 200;
}

int CGrass::Update()
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

void CGrass::Late_Update()
{
}

void CGrass::Render(HDC _DC)
{
}

void CGrass::Release()
{
}
