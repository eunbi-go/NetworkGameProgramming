#include "stdafx.h"
#include "Player.h"
#include "Bomb.h"
#include "ObjManager.h"
#include "KeyManager.h"
#include "LineManager.h"
#include "BmpManager.h"
#include "SoundMgr.h"
#include "SceneManager.h"
#include "ClientManager.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	//50 60
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Bazzi/bazzi.bmp", L"Bazzi");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Bazzi/bazzi_bubble.bmp", L"BazziBubble");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Bazzi/die.bmp", L"BazziPop");

	m_tInfo.fX = MAPSTARTX + (TILECX >> 1);
	m_tInfo.fY = MAPSTARTY + (TILECY >> 1);
	m_tInfo.iCX = 25;
	m_tInfo.iCY = 25;

	m_tInfo.iBombPower = 1;

	m_tInfo.iHP = 1;
	m_tInfo.iMaxBomb = 1;

	m_tInfo.fSpeed = 3.f;
	m_tInfo.bisDead = false;
	
	m_eState = OBJSTATE::IDLE;
	m_eCurDir = OBJDIR::IDLE;

	//CClientManager::Get_Instance()->setPlayerInfo(m_tInfo);
}

int CPlayer::Update()
{
	if (OBJSTATE::BUBBLE == m_eState)
	{
		if (m_dwTime + 6000 < GetTickCount())
		{
			m_eState = OBJSTATE::DEAD;
			m_dwTime = GetTickCount();
		}
		
	}
	if (OBJSTATE::DEAD == m_eState)
	{
		if (m_dwTime + 2000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"lose.mp3", CSoundMgr::PLAYER_LOSE);
			CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENE_MENU);
			return OBJ_DEAD;
		}
	}



	if (OBJSTATE::IDLE == m_eState)
		Key_Check();

	Update_Rect();
	Scene_Change();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CPlayer::Late_Update()
{


	if (m_tInfo.fX < 32)
		m_tInfo.fX += m_tInfo.fSpeed;

	if (m_tInfo.fX > 605)
		m_tInfo.fX -= m_tInfo.fSpeed;

	if (m_tInfo.fY < 52)
		m_tInfo.fY += m_tInfo.fSpeed;

	if (m_tInfo.fY > 547)
		m_tInfo.fY -= m_tInfo.fSpeed;
}

void CPlayer::Render(HDC _DC)
{
	Update_Rect();
	HDC hMemDC;
	switch (m_eState)
	{
	case OBJSTATE::IDLE:
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Bazzi");
		GdiTransparentBlt(_DC, m_tRect.left - 15, m_tRect.top - 30
			, 50, 60, hMemDC
			, m_tFrame.iFrameStart * 50, m_tFrame.iFrameScene * 60
			, 50, 60
			, RGB(100, 100, 100));
		break;
	case OBJSTATE::BUBBLE:
		m_tFrame.iFrameEnd = 6;
		m_tFrame.dwFrameSpeed = 1000;

		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BazziBubble");
		GdiTransparentBlt(_DC, m_tRect.left - 5, m_tRect.top - 20
			, 50, 60, hMemDC
			, m_tFrame.iFrameStart * 60, 0
			, 60, 60
			, RGB(100, 100, 100));
		break;
	case OBJSTATE::DEAD:
		m_tFrame.iFrameEnd = 12;
		m_tFrame.dwFrameSpeed = 400;

		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BazziPop");
		GdiTransparentBlt(_DC, m_tRect.left - 5, m_tRect.top - 20
			, 50, 60, hMemDC
			, m_tFrame.iFrameStart * 73, 0
			, 73, 120
			, RGB(255, 0, 255));
		break;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}


void CPlayer::Key_Check()
{

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_tInfo.fSpeed;
		m_eCurDir = OBJDIR::LEFT;
	}
	else if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_tInfo.fSpeed;
		m_eCurDir = OBJDIR::RIGHT;
	}
	else if (CKeyManager::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_tInfo.fSpeed;
		m_eCurDir = OBJDIR::TOP;
	}
	else if (CKeyManager::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_tInfo.fSpeed;
		m_eCurDir = OBJDIR::BOTTOM;
	}
	else
		m_eCurDir = OBJDIR::IDLE;

	if (CKeyManager::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"bomb_set.mp3", CSoundMgr::BOMB);
		if (m_tInfo.iMaxBomb > CObjManager::Get_Instance()->Get_BombSize())
		{
			int iBombPosTemp;
			if (((int)m_tInfo.fX % TILECX) > 5)
			{
				iBombPosTemp = ((int)m_tInfo.fX / TILECX) + 1;
			}
			else
				iBombPosTemp = ((int)m_tInfo.fX / TILECX);

			int fBombX = (int)(TILECX * iBombPosTemp);
			int fBombY = (int)(TILECY * ((int)m_tInfo.fY / TILECY));

			CObj* pObj = CAbstractFactory<CBomb>::Create(fBombX, fBombY + 15, m_tInfo.iBombPower, false);
			CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOMB);
		}
	}

}

void CPlayer::Scene_Change()
{
	if (m_ePreDir != m_eCurDir)
	{
		switch (m_eCurDir)
		{
		case OBJDIR::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = OBJDIR::IDLE;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 500;
			break;
		case OBJDIR::TOP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = OBJDIR::TOP;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 200;
			break;
		case OBJDIR::BOTTOM:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = OBJDIR::BOTTOM;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 200;
			break;
		case OBJDIR::LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = OBJDIR::LEFT;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 200;
			break;
		case OBJDIR::RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = OBJDIR::RIGHT;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 200;
			break;
		}
		m_ePreDir = m_eCurDir;
	}
}
