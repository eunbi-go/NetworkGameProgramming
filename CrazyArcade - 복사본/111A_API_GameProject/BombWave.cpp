#include "stdafx.h"
#include "BombWave.h"
#include "BmpManager.h"
#include "ObjManager.h"
#include "KeyManager.h"

CBombWave::CBombWave()
	: dWaveTime(GetTickCount()), m_eDir(OBJDIR::END)
{
}


CBombWave::~CBombWave()
{
	Release();
}

void CBombWave::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/bomb_line.bmp", L"BombLine");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/down1.bmp", L"BombDownEND");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/down2.bmp", L"BombDown");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/left1.bmp", L"BombLeftEND");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/left2.bmp", L"BombLeft");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/right1.bmp", L"BombRightEND");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/right2.bmp", L"BombRight");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/up1.bmp", L"BombUpEND");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Bomb/up2.bmp", L"BombUp");

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 200;
}

int CBombWave::Update()
{
	if (m_tInfo.bisDead)
		return OBJ_DEAD;



	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CBombWave::Late_Update()
{
	if (dWaveTime + 300 < GetTickCount())
	{
		m_tInfo.bisDead = true;
		dWaveTime = GetTickCount();
	}
}

void CBombWave::Render(HDC _DC)
{
	Update_Rect();
	if (m_eDir == OBJDIR::TOPEND)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombUpEND");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::LEFTEND)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombLeftEND");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::RIGHTEND)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombRightEND");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::BOTTOMEND)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombDownEND");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}


	//////////////////////////////////////////////////////////////////
	if (m_eDir == OBJDIR::TOP)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombUp");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::LEFT)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombLeft");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::RIGHT)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombRight");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::BOTTOM)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombDown");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0 * m_tFrame.iFrameStart, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (m_eDir == OBJDIR::IDLE)
	{
		HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"BombLine");
		GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY, hMemDC,
			0, 0,
			40, 40,
			RGB(255, 0, 255));
	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LCONTROL))
		Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBombWave::Release()
{
}
