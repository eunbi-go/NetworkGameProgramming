#pragma once

#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

class CScene;
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

public:
	enum SCENEID { SCENE_LOGO, SCENE_MENU,SCENE_EDIT, SCENE_WATINGROOM, SCENE_STAGE1,
	SCENE_STAGE2, SCENE_STAGE_BOSS, SCENE_STAGE_NETWORK, SCENE_END };

public:
	void Scene_Change(SCENEID _eScene);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	CHARNAME::NAME Get_Char() { return m_eChar; }
	void Set_Char(CHARNAME::NAME _char) { m_eChar = _char; }

	SCENEID	Get_CurScene() { return m_eCurScene; }

public:
	static CSceneManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}


private:
	static CSceneManager*		m_pInstance;
	CScene*						m_pScene;
	SCENEID				m_ePreScene;
	SCENEID				m_eCurScene;
	CHARNAME::NAME		m_eChar;
};


#endif // !__SCENEMANAGER_H__
