#include "stdafx.h"
#include "Bomb.h"
#include "Obj.h"
#include "BombWave.h"
#include "ObjManager.h"
#include "BmpManager.h"
#include "CollidManager.h"
#include "TileManager.h"
#include "KeyManager.h"
#include "SoundMgr.h"

CBomb::CBomb()
	: dBombTime(GetTickCount()), m_Wavecnt(1),
	iRightBombPower(0),
	iLeftBombPower(0),
	iUpBombPower(0),
	iDownBombPower(0)
{
}


CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/bomb.bmp", L"Bomb");

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;


	m_tInfo.fX = MAPSTARTX + ((m_tInfo.fX / TILECX) * TILECX);
	m_tInfo.fY = MAPSTARTY + ((m_tInfo.fY / TILECY) * TILECY);
	CTileManager::Get_Instance()->SetTileBlockType(m_tInfo.fX, m_tInfo.fY, MAPBLOCK::BOMB);

	//m_tRect.left = MAPSTARTX + m_tInfo.fX * TILECX;
	//m_tRect.right = m_tRect.left + TILEX;
	//m_tRect.top = MAPSTARTY + m_tInfo.fY * TILECY;
	//m_tRect.bottom = m_tRect.top + TILECY;



	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iFrameScene = OBJDIR::IDLE;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 500;
}

int CBomb::Update()
{
	int ibombPosX = (int)m_tInfo.fX;
	int ibombPosY = (int)m_tInfo.fY;

	CObj* pObj;

	if (m_tInfo.bisDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"wave.mp3", CSoundMgr::BOMBPOP);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);

		// 오른쪽 물줄기 MAX 정하기
		for (int i = 1; i <= m_tInfo.iBombPower; ++i)
		{
			iRightBombPower = m_tInfo.iBombPower;
			// 맵 밖으로 안나가게 검사
			if (m_tInfo.fX + (TILECX * i) >= 620)
			{
				iRightBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 있으면 최대물줄기파워 제한
			if (MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5))
			{
				iRightBombPower = i;
				break;
			}

			else if (MAPBLOCK::ROCK1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::ROCK2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::ROCK3 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX + (TILECX * i), m_tInfo.fY + 5))
			{
				iRightBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 없으면 최대물줄기파워
			else
				iRightBombPower = m_tInfo.iBombPower;
		}

		// 위쪽 물줄기 MAX 정하기
		for (int i = 1; i <= m_tInfo.iBombPower; ++i)
		{
			// 맵 밖으로 안나가게 검사
			if (m_tInfo.fY - (TILECY * i) <= 40)
			{
				iUpBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 있으면 최대물줄기파워 제한
			if (MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)) ||
				MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)) ||
				MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)) ||
				MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)) ||
				MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)))
			{
				iUpBombPower = i;
				break;
			}

			else if (MAPBLOCK::ROCK1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)) ||
				MAPBLOCK::ROCK2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)) ||
				MAPBLOCK::ROCK3 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 - (TILECY * i)))
			{
				iUpBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 없으면 최대물줄기파워
			else
				iUpBombPower = m_tInfo.iBombPower;
		}

		// 왼쪽 물줄기 MAX 정하기
		for (int i = 1; i <= m_tInfo.iBombPower; ++i)
		{
			// 맵 밖으로 안나가게 검사
			if (m_tInfo.fX - (TILECX * i) <= MAPSTARTX)
			{
				iLeftBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 있으면 최대물줄기파워 제한
			if (MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5))
			{
				iLeftBombPower = i;
				break;
			}

			else if (MAPBLOCK::ROCK1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::ROCK2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5) ||
				MAPBLOCK::ROCK3 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX - (TILECX * i), m_tInfo.fY + 5))
			{
				iLeftBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 없으면 최대물줄기파워
			else
				iLeftBombPower = m_tInfo.iBombPower;
		}

		// 아래쪽 물줄기 MAX 정하기
		for (int i = 1; i <= m_tInfo.iBombPower; ++i)
		{
			// 맵 밖으로 안나가게 검사
			if (m_tInfo.fY + (TILECY * i) >= 560)
			{
				iDownBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 있으면 최대물줄기파워 제한
			if (MAPBLOCK::BASKET == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)) ||
				MAPBLOCK::LEAF1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)) ||
				MAPBLOCK::LEAF2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)) ||
				MAPBLOCK::FLOWER == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)) ||
				MAPBLOCK::GRASS == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)))
			{
				iDownBombPower = i;
				break;
			}

			else if (MAPBLOCK::ROCK1 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)) ||
				MAPBLOCK::ROCK2 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)) ||
				MAPBLOCK::ROCK3 == CTileManager::Get_Instance()->GetTileBlockType(m_tInfo.fX, m_tInfo.fY + 5 + (TILECY * i)))
			{
				iDownBombPower = i - 1;
				break;
			}
			// 물줄기 범위에 블록이 없으면 최대물줄기파워
			else
				iDownBombPower = m_tInfo.iBombPower;
		}



		// 오른쪽 물줄기 발사
		for (int i = 1; i <= iRightBombPower; ++i)
		{
			if (i == iRightBombPower)
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX + TILECX * i, m_tInfo.fY, OBJDIR::RIGHTEND);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
			else
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX + TILECX * i, m_tInfo.fY, OBJDIR::RIGHT);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
		}

		// 위쪽 물줄기 발사
		for (int i = 1; i <= iUpBombPower; ++i)
		{
			if (i == iUpBombPower)
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY - TILECY * i, OBJDIR::TOPEND);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
			else
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY - TILECY * i, OBJDIR::TOP);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
		}

		// 왼쪽 물줄기 발사
		for (int i = 1; i <= iLeftBombPower; ++i)
		{
			if (i == iLeftBombPower)
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX - TILECX * i, m_tInfo.fY, OBJDIR::LEFTEND);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
			else
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX - TILECX * i, m_tInfo.fY, OBJDIR::LEFT);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
		}

		// 아래쪽 물줄기 발사
		for (int i = 1; i <= iDownBombPower; ++i)
		{
			if (i == iDownBombPower)
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY + TILECY * i, OBJDIR::BOTTOMEND);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
			else
			{
				pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY + TILECY * i, OBJDIR::BOTTOM);
				CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
			}
		}

		return OBJ_DEAD;
	}
	m_PlayerX = CObjManager::Get_Instance()->Get_PlayerX();
	m_PlayerY = CObjManager::Get_Instance()->Get_PlayerY();

	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CBomb::Late_Update()
{
	if (dBombTime + 4000 < GetTickCount())
	{
		m_tInfo.bisDead = true;
		dBombTime = GetTickCount();
	}
}

void CBomb::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Bomb");
	
	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY, hMemDC,
		40 * m_tFrame.iFrameStart, 0,
		40, 40,
		RGB(100, 100, 100));

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBomb::Release()
{
}
