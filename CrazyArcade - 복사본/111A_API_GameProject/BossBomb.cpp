#include "stdafx.h"
#include "BossBomb.h"
#include "BombWave.h"
#include "ObjManager.h"
#include "BmpManager.h"
#include "CollidManager.h"
#include "TileManager.h"
#include "KeyManager.h"
#include "SoundMgr.h"

CBossBomb::CBossBomb()
	: dBombTime(GetTickCount())
{
}


CBossBomb::~CBossBomb()
{
	Release();
}

void CBossBomb::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/bomb.bmp", L"Bomb");

	m_tInfo.iCX = 120;
	m_tInfo.iCY = 120;


	m_tInfo.fX = MAPSTARTX + ((m_tInfo.fX / TILECX) * TILECX);
	m_tInfo.fY = MAPSTARTY + ((m_tInfo.fY / TILECY) * TILECY);
	CTileManager::Get_Instance()->SetTileBlockType(m_tInfo.fX, m_tInfo.fY, MAPBLOCK::BOMB);

	//m_tRect.left = MAPSTARTX + m_tInfo.fX * TILECX;
	//m_tRect.right = m_tRect.left + TILEX;
	//m_tRect.top = MAPSTARTY + m_tInfo.fY * TILECY;
	//m_tRect.bottom = m_tRect.top + TILECY;


}

int CBossBomb::Update()
{
	CObj* pObj;

	m_tInfo.fY += 5.f;

	if (m_tInfo.bisDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"wave.mp3", CSoundMgr::BOMBPOP);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX - TILECX, m_tInfo.fY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX + TILECX, m_tInfo.fY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX + TILECX, m_tInfo.fY - TILECY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX + TILECX, m_tInfo.fY + TILECY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX - TILECX, m_tInfo.fY + TILECY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX - TILECX, m_tInfo.fY - TILECY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY + TILECY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);
		pObj = CAbstractFactory<CBombWave>::Create(m_tInfo.fX, m_tInfo.fY - TILECY, OBJDIR::IDLE);
		CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMBWAVE);

		
		return OBJ_DEAD;
	}


	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CBossBomb::Late_Update()
{
	if (dBombTime + 1000 < GetTickCount())
	{
		m_tInfo.bisDead = true;
		dBombTime = GetTickCount();
	}
}

void CBossBomb::Render(HDC _DC)
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

void CBossBomb::Release()
{
}
