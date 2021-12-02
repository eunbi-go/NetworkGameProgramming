#include "stdafx.h"
#include "MapManager.h"
#include "StageMap.h"

CMapManager* CMapManager::m_pInstance = nullptr;

CMapManager::CMapManager()
{
}


CMapManager::~CMapManager()
{
	Release();
}

void CMapManager::Update()
{
	for (int i = 0; i < MAPBLOCK::END; ++i)
	{
		for (auto& iter = m_pMapObj[i].begin(); iter != m_pMapObj[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (iEvent == OBJ_DEAD)
			{
				SAFE_DELETE(*iter);
				iter = m_pMapObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CMapManager::Late_Update()
{
	for (int i = 0; i < MAPBLOCK::END; ++i)
	{
		for (auto& pObj : m_pMapObj[i])
			pObj->Late_Update();
	}
}

void CMapManager::Render(HDC _DC)
{
	for (int i = 0; i < MAPBLOCK::END; ++i)
	{
		for (auto& pObj : m_pMapObj[i])
			pObj->Render(_DC);
	}
}

void CMapManager::Release()
{
	for (int i = 0; i < MAPBLOCK::END; ++i)
	{
		for_each(m_pMapObj[i].begin(), m_pMapObj[i].end(), Safe_Delete<CStageMap*>);
		m_pMapObj[i].clear();
	}
}
