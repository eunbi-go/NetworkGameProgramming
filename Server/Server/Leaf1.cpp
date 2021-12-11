#include "stdafx.h"
#include "Leaf1.h"
//#include "BmpManager.h"
#include "ObjManager.h"
//#include "KeyManager.h"
#include "TileManager.h"
#include "Ballon.h"
#include "Potion.h"
#include "MaxPotion.h"
#include "Skate.h"

CLeaf1::CLeaf1()
{
}


CLeaf1::~CLeaf1()
{
	Release();
}

void CLeaf1::Initialize()
{
	m_eBlock = MAPBLOCK::LEAF1;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_eState = OBJSTATE::IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 200;
}

int CLeaf1::Update()
{
	CObj* pObj = nullptr;

	if (m_eState == OBJSTATE::BUBBLE)
	{
		CTileManager::Get_Instance()->SetTileBlockType(m_tInfo.fX, m_tInfo.fY, MAPBLOCK::NOBLOCK);
		int iItem = rand() % 5;
		switch (iItem)
		{
		case 0:
			pObj = CAbstractFactory<CBallon>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjManager::Get_Instance()->Add_Object_Item(pObj, GAMEITEM::BALLON);
			break;
		case 1:
			pObj = CAbstractFactory<CPotion>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjManager::Get_Instance()->Add_Object_Item(pObj, GAMEITEM::POTION);
			break;
		case 2:
			pObj = CAbstractFactory<CSkate>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjManager::Get_Instance()->Add_Object_Item(pObj, GAMEITEM::SKATE);
			break;
		case 3:
			pObj = CAbstractFactory<CMaxPotion>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjManager::Get_Instance()->Add_Object_Item(pObj, GAMEITEM::MAXPOTION);
			break;
		case 4:
			break;
		}
		return OBJ_DEAD;
	}


	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CLeaf1::Late_Update()
{
}

void CLeaf1::Render(HDC _DC)
{
}

void CLeaf1::Release()
{
}
