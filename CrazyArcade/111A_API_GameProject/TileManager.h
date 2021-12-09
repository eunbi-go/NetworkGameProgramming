#pragma once

#ifndef __TILEMANAGER_H__
#define __TILEMANAGER_H__

class CTileManager
{
public:
	CTileManager();
	~CTileManager();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Picking_Tile(int _iDrawID);
	void Save_Tile();
	void Load_Tile();

public:
	void SetTileBlockType(float _x, float _y, MAPBLOCK::BLOCK _block);
	void Set_vecMapTile(vector<CObj*> vObj) { m_vecTile = vObj; }
	void Set_DataFile(char* Name, int len);

public:
	MAPBLOCK::BLOCK GetTileBlockType(float _x, float _y);
	vector<int>	Get_vecCollTileKey() { return m_vecCollTileKey; }

public:
	void CollByBomb(int nKey) { m_vecCollTileKey.emplace_back(nKey); }
	void Organize_Tile();
	void Clear_vecCollTileKey() { m_vecCollTileKey.clear(); }
	void Add_CollTileKey(int nKey);

public:
	static CTileManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CTileManager* m_pInstance;
	vector<CObj*>				m_vecTile;
	CTile* m_Tile[TILEX][TILEY];
	char* m_fileName;

	vector<int>					m_vecCollTileKey;
};


#endif // !__TILEMANAGER_H__
