#pragma once

#ifndef __TILEMANAGER_H__
#define __TILEMANAGER_H__

class CTileManager
{
public:
	CTileManager();
	~CTileManager();

public:
	void Load_Tile();

	void Release();

public:
	void SetTileBlockType(float _x, float _y, MAPBLOCK::BLOCK _block);

public:
	MAPBLOCK::BLOCK GetTileBlockType(float _x, float _y);
	vector<CObj*>	Get_MapTile() { return m_vecTile; }
	vector<int>		Get_DeadTile() { return m_vecDeadTileKey; }

public:
	void Organize_vecTile(vector<int> vecTileKey);
	void Clear_DeadTileKey() { m_vecDeadTileKey.clear(); }

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
	vector<CObj*>			m_vecTile;
	CTile* m_Tile[TILEX][TILEY];
	vector<int>				m_vecDeadTileKey;
};


#endif // !__TILEMANAGER_H__
