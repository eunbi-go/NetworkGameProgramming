#include "stdafx.h"
#include "MyMenu.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "SoundMgr.h"

CMyMenu::CMyMenu()
{
	
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Default/Menu.bmp", L"Menu");
	CSoundMgr::Get_Instance()->PlayBGM(L"Menu.mp3");
}

void CMyMenu::Update()
{
	
}

void CMyMenu::Late_update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (318 < pt.x && 470 > pt.x
			&& 44 < pt.y && 194 > pt.y)
		{
			CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENE_WATINGROOM);
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
		}

		return;
	}
	if (CKeyManager::Get_Instance()->Key_Down('E'))
	{
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENE_EDIT);
		return;
	}
}

void CMyMenu::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Menu");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CMyMenu::Release()
{
	
}
