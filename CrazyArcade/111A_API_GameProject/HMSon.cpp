#include "stdafx.h"
#include "HMSon.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "ObjManager.h"
#include "TileManager.h"
#include "BossBomb.h"
#include "BombWave.h"
#include "SoundMgr.h"
#include "SceneManager.h"

CHMSon::CHMSon()
{
}


CHMSon::~CHMSon()
{
	Release();
}


void CHMSon::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon.bmp", L"HMSon");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_left.bmp", L"HMSon_Left");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Right.bmp", L"HMSon_Right");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Bottom.bmp", L"HMSon_Bottom");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Attack.bmp", L"HMSon_Attack");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Bubble.bmp", L"HMSon_Bubble");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Hit.bmp", L"HMSon_Hit");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Pop.bmp", L"HMSon_Pop");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Monster/HMSon_Scroll.bmp", L"HMSon_Scroll");

	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_tInfo.fSpeed = 1.f;

	m_eState = OBJSTATE::IDLE;

	m_tInfo.iHP = 2;
	m_bossFrame = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 500;

}

int CHMSon::Update()
{
	if (m_dwTime + 7000 < GetTickCount())
	{
		Bomb_Drop();

		m_dwTime = GetTickCount();
	}

	if (m_eState == OBJSTATE::ATTACK)
	{
		if (m_dwTime + 2000 < GetTickCount())
		{
			m_eState = OBJSTATE::IDLE;
			m_dwTime = GetTickCount();
		}
	}

	if (OBJSTATE::IDLE == m_eState)
	{
		switch (m_eCurDir)
		{
		case OBJDIR::TOP:
			m_tInfo.fY -= m_tInfo.fSpeed * 5;
			m_tInfo.fX -= m_tInfo.fSpeed * 5;
			break;
		case OBJDIR::BOTTOM:
			m_tInfo.fY += m_tInfo.fSpeed;
			break;
		case OBJDIR::LEFT:
			m_tInfo.fX -= m_tInfo.fSpeed;
			break;
		case OBJDIR::RIGHT:
			m_tInfo.fX += m_tInfo.fSpeed;
			break;
		}
	}

	if (OBJSTATE::HIT == m_eState)
	{
		CObjManager::Get_Instance()->Set_BossHP(1);
		m_eState = OBJSTATE::IDLE;

	}

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
			CObjManager::Get_Instance()->Set_Stage1Clear(1);
			return OBJ_DEAD;
		}
	}

	if (CObjManager::Get_Instance()->Get_BossHP() >= 50)
		m_tInfo.fSpeed = 2.f;

	if (CObjManager::Get_Instance()->Get_BossHP() >= 100)
	{
		m_eState = OBJSTATE::BUBBLE;
	}

	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CHMSon::Late_Update()
{
	if (m_eCurDir == OBJDIR::LEFT)
	{
		if (m_tInfo.fX + 1 - (TILECX >> 1) < 60)
		{
			m_tInfo.fX += m_tInfo.fSpeed;
			m_eCurDir = OBJDIR::BOTTOM;
			
		}
	}

	if (m_eCurDir == OBJDIR::RIGHT)
	{
		if (m_tInfo.fX + 1 + (TILECX >> 1) > 600)
		{
			m_tInfo.fX -= m_tInfo.fSpeed;
			m_eCurDir = OBJDIR::TOP;
		}
	}

	if (m_eCurDir == OBJDIR::TOP)
	{
		if (m_tInfo.fY + 1 - (TILECY >> 1) < 50)
		{
			m_tInfo.fY += m_tInfo.fSpeed;
			m_eCurDir = OBJDIR::LEFT;
		}
		
	}

	if (m_eCurDir == OBJDIR::BOTTOM)
	{
		if (m_tInfo.fY + 1 + (TILECY >> 1) > 500)
		{
			m_tInfo.fY -= m_tInfo.fSpeed;
			m_eCurDir = OBJDIR::RIGHT;
		}
		
	}
}

void CHMSon::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon");

	if (OBJSTATE::IDLE == m_eState)
	{
		switch (m_eCurDir)
		{
		case OBJDIR::TOP:
			hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Scroll");
			m_tFrame.iFrameEnd = 3;
			GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 60
				, 180, 204, hMemDC
				, m_tFrame.iFrameStart * 95, 20
				, 95, 110
				, RGB(255, 255, 255));
			break;
		case OBJDIR::BOTTOM:
			hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Bottom");
			m_tFrame.iFrameEnd = 1;
			GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 60
				, 180, 204, hMemDC
				, m_tFrame.iFrameStart * 80, 20
				, 90, 110
				, RGB(255, 255, 255));
			break;
		case OBJDIR::LEFT:
			hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Left");
			m_tFrame.iFrameEnd = 1;
			GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 60
				, 180, 204, hMemDC
				, 10 + m_tFrame.iFrameStart * 110, 20
				, 110, 110
				, RGB(255, 255, 255));
			break;
		case OBJDIR::RIGHT:
			hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Right");
			m_tFrame.iFrameEnd = 1;
			GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 60
				, 180, 204, hMemDC
				, 10 + m_tFrame.iFrameStart * 110, 20
				, 110, 110
				, RGB(255, 255, 255));
			break;
		}
	}

	if (m_eState == OBJSTATE::HIT)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Hit");
		m_tFrame.dwFrameSpeed = 800;
		GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 20
			, 180, 204, hMemDC
			, 0, 20
			, 90, 102
			, RGB(255, 255, 255));
	}

	if (m_eState == OBJSTATE::ATTACK)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Attack");
		m_tFrame.dwFrameSpeed = 300;
		m_tFrame.iFrameEnd = 1;
		GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 20
			, 180, 204, hMemDC
			, m_tFrame.iFrameStart * 116, 20
			, 116, 102
			, RGB(255, 255, 255));
	}

	if (m_eState == OBJSTATE::BUBBLE)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Bubble");
		m_tFrame.dwFrameSpeed = 300;
		m_tFrame.iFrameEnd = 1;
		GdiTransparentBlt(_DC, m_tRect.left - 22, m_tRect.top - 70
			, 180, 204, hMemDC
			, m_bossFrame * 105, 20
			, 105, 102
			, RGB(255, 255, 255));
		m_bossFrame = 1;
	}

	if (m_eState == OBJSTATE::DEAD)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"HMSon_Pop");
		m_tFrame.dwFrameSpeed = 300;
		m_tFrame.iFrameEnd = 2;
		GdiTransparentBlt(_DC, m_tRect.left - 52, m_tRect.top - 20
			, 180, 204, hMemDC
			, m_tFrame.iFrameStart * 108, 20
			, 108, 102
			, RGB(255, 255, 255));
	}




	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CHMSon::Bomb_Drop()
{
	m_eState = OBJSTATE::ATTACK;

	int BossBombX = rand() % 600 + 20;
	int BossBombY = rand() % 400;

	int BossBombX2 = rand() % 600 + 20;
	int BossBombY2 = rand() % 400;

	CObj* pObj = CAbstractFactory<CBossBomb>::Create(BossBombX, BossBombY, m_tInfo.iBombPower, false);
	CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOSSBOMB);

	pObj = CAbstractFactory<CBossBomb>::Create(BossBombX2, BossBombY2, m_tInfo.iBombPower, false);
	CObjManager::Get_Instance()->Add_Object(pObj, OBJID::BOSSBOMB);
}



void CHMSon::Release()
{
}
