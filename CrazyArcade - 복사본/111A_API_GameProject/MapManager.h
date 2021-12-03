#pragma once

#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

class CStageMap;
class CMapManager
{
public:
	CMapManager();
	~CMapManager();

public:
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Add_Block(CStageMap* _pObj, MAPBLOCK::BLOCK _eID) { m_pMapObj[_eID].emplace_back(_pObj); }

public:
	list<CStageMap*> Get_MapTile() { return m_pMapObj[MAPBLOCK::BASKET]; }

public:
	static CMapManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CMapManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}



private:
	static CMapManager*		m_pInstance;
	list<CStageMap*>		m_pMapObj[MAPBLOCK::END];
};


#endif // !__MAPMANAGER_H__