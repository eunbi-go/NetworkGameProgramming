#include "stdafx.h"
#include "TileManager.h"
#include "Tile.h"

CTileManager* CTileManager::m_pInstance = nullptr;

CTileManager::CTileManager()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			m_Tile[j][i] = nullptr;
		}
	}
}

CTileManager::~CTileManager()
{
	Release();
}

void CTileManager::Load_Tile()
{
	HANDLE hFile = CreateFile("../Data/Tile.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tTemp = {};
	int		iDrawID = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY);
		dynamic_cast<CTile*>(pObj)->Set_TileKey(iDrawID);

		m_vecTile.emplace_back(pObj);
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공", L"성공", MB_OK);
}

void CTileManager::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

void CTileManager::SetTileBlockType(float _x, float _y, MAPBLOCK::BLOCK _block)
{
}

MAPBLOCK::BLOCK CTileManager::GetTileBlockType(float _x, float _y)
{
	return MAPBLOCK::BLOCK();
}
