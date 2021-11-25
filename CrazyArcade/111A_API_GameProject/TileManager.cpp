#include "stdafx.h"
#include "TileManager.h"
#include "Tile.h"
#include "BmpManager.h"
#include "KeyManager.h"
#include "ClientManager.h"

CTileManager* CTileManager::m_pInstance = nullptr;
CTileManager::CTileManager()
	
{
	//m_vecTile.reserve(TILEX * TILEY);
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

void CTileManager::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (float) MAPSTARTX + (j * TILECX) + (TILECX >> 1);
			float fY = (float) MAPSTARTY + (i * TILECY) + (TILECY >> 1);

			CObj* pObj = CAbstractFactory<CTile>::Create(fX, fY);
			m_Tile[j][i] = dynamic_cast<CTile*>(pObj);
			dynamic_cast<CTile*>(m_Tile[j][i])->SetTileType(MAPBLOCK::NOBLOCK);
			m_vecTile.emplace_back(pObj);
		}
	}
}

void CTileManager::Update()
{

}

void CTileManager::Late_Update()
{
}

void CTileManager::Render(HDC _DC)
{
	for (auto& pTile : m_vecTile)
		pTile->Render(_DC);
}

void CTileManager::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

void CTileManager::Picking_Tile(int _iDrawID)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	int x = (pt.x - MAPSTARTX) / TILECX ;
	int y = (pt.y - MAPSTARTY) / TILECY;
	
	int iIdx = TILEX * y + x;

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIdx])->Set_TileKey(_iDrawID);
}



void CTileManager::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &dynamic_cast<CTile*>(pTile)->Get_TileKey(), sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OK);
}

void CTileManager::Load_Tile()
{
	wchar_t pwstrName[100];
	//char* fileName = "../111A_API_GameProject/Tile.dat";
	int iLen = (int)strlen(m_fileName) + 1;
	size_t con = 0;
	mbstowcs_s(&con, pwstrName, m_fileName, iLen);

	//HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ
	//	, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hFile = CreateFile(pwstrName, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패", L"실패", MB_OK);
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

void CTileManager::SetTileBlockType(float _x, float _y, MAPBLOCK::BLOCK _block)
{
	int TileX = ((int)_x - MAPSTARTX) / TILECX;
	int TileY = ((int)_y - MAPSTARTY) / TILECY;



	if (!m_Tile[TileX][TileY])
		return;

	m_Tile[TileX][TileY]->SetTileType(_block);
}

void CTileManager::Set_DataFile(char* Name, int len)
{
	m_fileName = Name;
}

MAPBLOCK::BLOCK CTileManager::GetTileBlockType(float _x, float _y)
{
	int TileX = ((int)_x - MAPSTARTX) / TILECX;
	int TileY = ((int)_y - MAPSTARTY) / TILECY;

	return m_Tile[TileX][TileY]->GetTileType();
}





