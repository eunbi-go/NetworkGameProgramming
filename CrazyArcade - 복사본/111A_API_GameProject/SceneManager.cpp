#include "stdafx.h"
#include "SceneManager.h"
#include "Logo.h"
#include "MyMenu.h"
#include "WatingRoom.h"
#include "Stage1.h"
#include "MyEdit.h"
#include "Stage2.h"
#include "Stage_Boss.h"
#include "CNetworkStage.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;
CSceneManager::CSceneManager()
	:m_pScene(nullptr), m_eCurScene(SCENE_END), m_ePreScene(SCENE_END)
{
}


CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Scene_Change(SCENEID _eScene)
{
	m_eCurScene = _eScene;
	if (m_ePreScene != m_eCurScene)
	{
		SAFE_DELETE(m_pScene);

		switch (m_eCurScene)
		{
		case CSceneManager::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneManager::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case CSceneManager::SCENE_WATINGROOM:
			m_pScene = new CWatingRoom;
			break;
		case CSceneManager::SCENE_EDIT:
			m_pScene = new CMyEdit;
			break;
		case CSceneManager::SCENE_STAGE1:
			m_pScene = new CStage1;
			break;
		case CSceneManager::SCENE_STAGE2:
			m_pScene = new CStage2;
			break;
		case CSceneManager::SCENE_STAGE_BOSS:
			m_pScene = new CStage_Boss;
			break;
		case CSceneManager::SCENE_STAGE_NETWORK:
			m_pScene = new CNetworkStage;
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::Late_Update()
{
	m_pScene->Late_update();
}

void CSceneManager::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneManager::Release()
{
	SAFE_DELETE(m_pScene);
}
