#include "stdafx.h"
#include "Logo.h"
#include "BmpManager.h"
#include "SceneManager.h"

CLogo::CLogo()
	:m_dwTime(GetTickCount())
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Logo.bmp", L"Logo");
}

void CLogo::Update()
{
	if (m_dwTime + 2000 < GetTickCount())
	{
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENE_MENU);
		return;
		//m_dwTime = GetTickCount();
	}
}

void CLogo::Late_update()
{
}

void CLogo::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Logo");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
