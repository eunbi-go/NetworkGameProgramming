#include "stdafx.h"
#include "WatingRoom.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "SoundMgr.h"
#include "ClientManager.h"

CWatingRoom::CWatingRoom()
{
}


CWatingRoom::~CWatingRoom()
{
	Release();
}

void CWatingRoom::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/3PLobby.bmp", L"Lobby");
	
	// 캐릭터 썸네일
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Bazzi/bazzi_image.bmp", L"Bazzi_sumnail");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Bazzi/bazzi.bmp", L"bazzi");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Dao/dao_image.bmp", L"Dao_sumanil");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Dao/dao.bmp", L"dao");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Digenie/digenie_image.bmp", L"Digenie_sumnail");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Digenie/digenie.bmp", L"degenie");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Uni/uni_image.bmp", L"Uni_sumnail");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Obj/Character/Uni/uni.bmp", L"uni");
	CSoundMgr::Get_Instance()->PlaySound(L"Lobby.mp3", CSoundMgr::LOBBY);

	m_tInfo.fX = 75;
	m_tInfo.fY = 140;
	m_tInfo.iCX = 25;
	m_tInfo.iCY = 25;

	// 캐릭터 이미지 나중에 추가할꺼임
}

void CWatingRoom::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CWatingRoom::Update()
{
	Update_Rect();
}

void CWatingRoom::Late_update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (515 < pt.x && 700 > pt.x
			&& 496 < pt.y && 547 > pt.y)
		{
			CClientManager::Get_Instance()->setGameStart();
			CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENE_STAGE_NETWORK);
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::LOBBY);
		}

		// 캐릭터 선택

		if (488 < pt.x && 552 > pt.x
			&& 191 < pt.y && 230 > pt.y)
		{
			//다
		CSceneManager::Get_Instance()->Set_Char(CHARNAME::DAO);
		}

		if (562 < pt.x && 624 > pt.x
			&& 191 < pt.y && 230 > pt.y)
		{
			// 디
			CSceneManager::Get_Instance()->Set_Char(CHARNAME::DIGENIE);
		}

		if (633 < pt.x && 694 > pt.x
			&& 191 < pt.y && 230 > pt.y)
		{
			// 배
			CSceneManager::Get_Instance()->Set_Char(CHARNAME::BAZZI);
		}

		if (704 < pt.x && 768 > pt.x
			&& 191 < pt.y && 230 > pt.y)
		{
			// 우
			CSceneManager::Get_Instance()->Set_Char(CHARNAME::UNI);
		}

		return;
	}
}

void CWatingRoom::Render(HDC _DC)
{
	// ClientID별 캐릭터 위치
	// ClientID : 0  ->  50
	// ClientID : 1  ->  155
	// ClientID : 2  ->  260

	int iTempPos = 0;
	// 클라이언트 아이디 따라 위치 정해주기
	switch (CClientManager::Get_Instance()->GetClientID())
	{
	case 0:
		iTempPos = 50;
		break;
	case 1:
		iTempPos = 155;
		break;
	case 2:
		iTempPos = 260;
		break;
	}

	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Lobby");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	if (CSceneManager::Get_Instance()->Get_Char() == CHARNAME::BAZZI)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Bazzi_sumnail");
		BitBlt(_DC, 490, 10, 768, 91, hMemDC, 0, 0, SRCCOPY);
		
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"bazzi");
		GdiTransparentBlt(_DC, iTempPos, m_tRect.top
			, 50, 60, hMemDC
			, 0, 0
			, 50, 60
			, RGB(100, 100, 100));		
	}
	if (CSceneManager::Get_Instance()->Get_Char() == CHARNAME::DAO)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Dao_sumanil");
		BitBlt(_DC, 490, 10, 768, 91, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"dao");
		GdiTransparentBlt(_DC, iTempPos, m_tRect.top
			, 50, 60, hMemDC
			, 0, 0
			, 50, 60
			, RGB(100, 100, 100));
	}
	if (CSceneManager::Get_Instance()->Get_Char() == CHARNAME::DIGENIE)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Digenie_sumnail");
		BitBlt(_DC, 490, 10, 768, 91, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"degenie");
		GdiTransparentBlt(_DC, iTempPos, m_tRect.top
			, 50, 60, hMemDC
			, 0, 0
			, 50, 60
			, RGB(100, 100, 100));
	}
	if (CSceneManager::Get_Instance()->Get_Char() == CHARNAME::UNI)
	{
		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Uni_sumnail");
		BitBlt(_DC, 490, 10, 768, 91, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CBmpManager::Get_Instance()->Find_Image(L"uni");
		GdiTransparentBlt(_DC, iTempPos, m_tRect.top
			, 50, 60, hMemDC
			, 0, 0
			, 50, 60
			, RGB(100, 100, 100));
	}
}

void CWatingRoom::Release()
{
}
