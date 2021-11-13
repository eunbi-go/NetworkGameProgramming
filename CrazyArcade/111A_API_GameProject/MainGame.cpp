#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "ObjManager.h"
#include "KeyManager.h"
#include "BmpManager.h"
#include "SceneManager.h"
#include "TileManager.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/stage1.bmp", L"Stage1Back");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackBuffer");
	m_DC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();
	CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENEID::SCENE_MENU);
	CTileManager::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	CSceneManager::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneManager::Get_Instance()->Late_Update();
	CKeyManager::Get_Instance()->Key_Update();
}

void CMainGame::Render()
{
	HDC HMemDC = CBmpManager::Get_Instance()->Find_Image(L"Stage1Back");
	HDC HBackBuffer = CBmpManager::Get_Instance()->Find_Image(L"BackBuffer");

	BitBlt(HBackBuffer, 0, 0, WINCX, WINCY, HMemDC, 0, 0, SRCCOPY);

	CSceneManager::Get_Instance()->Render(HBackBuffer);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, HBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	CKeyManager::Destroy_Instance();
	CBmpManager::Destroy_Instance();
	CSceneManager::Destroy_Instance();
	CTileManager::Destroy_Instance();

	CObjManager::Destroy_Instance();
	CSoundMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
