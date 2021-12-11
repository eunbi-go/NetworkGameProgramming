#pragma once

#ifndef __OBJMANAGER_H__
#define __OBJMANAGER_H__

class CObj;
class CObjManager
{
public:
	CObjManager();
	~CObjManager();

public:
	void Update();
	void Update_Monster();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Add_Object(CObj* _pObj, OBJID::ID _eID) { m_listObj[_eID].emplace_back(_pObj); }
	void Add_Object_MapBlock(CObj* _pObj, MAPBLOCK::BLOCK _eBlock) { m_listMapBLOCK[_eBlock].emplace_back(_pObj); }
	void Add_Object_Item(CObj* _pObj, GAMEITEM::ITEM _eItem) { m_listItem[_eItem].emplace_back(_pObj); }

public:
	float Get_PlayerX();
	float Get_PlayerY();
	float Get_BombX();
	float Get_BombY();

	list<CObj*>	Get_MonsterList() { return m_listObj[OBJID::MONSTER]; }
	list<CObj*>	Get_ItemList() { return m_listItem[GAMEITEM::END]; }
	void Set_MonsterList(list<CObj*>& listM) { m_listObj[OBJID::MONSTER] = listM; }

	void Set_PlayerX(float fX);
	void Set_PlayerY(float fY);

public:
	int Get_BombSize() { return m_listObj[OBJID::BOMB].size(); }

public:
	void Picking_Object(CObj* _pObj, MAPBLOCK::BLOCK _block);
	void Save_Object();
	void Load_Object();
	void Save_Object_Stage2();
	void Load_Object_Stage2();
	void Save_Object_Boss();
	void Load_Object_Boss();

public:
	int Get_Stage1Clear() { return m_iStage1Clear; }
	int Get_BossHP() { return m_BossHP; }
	void Set_Stage1Clear(int _cnt) { m_iStage1Clear += _cnt; }
	void Set_BossHP(int _att) { m_BossHP += _att; }

	void Set_Cheat(bool _ischeat) { m_bisCheat = _ischeat; }
	bool Get_Cheat() { return m_bisCheat; }

public:
	vector<int>	Get_DeadTile() { return m_vecDeadTileKey; }
	void Clear_DeadTile() {
		m_vecDeadTileKey.clear();	m_vecDeadTileKey.resize(0); 
		m_vecItemKey.clear();		m_vecItemKey.resize(0); 
		m_vecItem.clear();			m_vecItem.resize(0);
	}
	void Add_DeadBlock(int iNum) {
		if (find(m_vecDeadBlockKey.begin(), m_vecDeadBlockKey.end(), iNum)
			== m_vecDeadBlockKey.end()) {
			m_vecDeadBlockKey.emplace_back(iNum);
		}
	}
	void Add_CollBlock(int iNum);

public:
	void Check_ItemBlock(int iNum);
	float Get_blockPosX(int iNum);
	float Get_blockPosY(int iNum);
	void Make_Item();
	//vector<int>	Get_vecItemkey() { return m_vecItemKey; }
	vector<ITEMINFO>	Get_vecItemInfo() { return m_vecItem; }

public:
	static CObjManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}



private:
	list<CObj*>				m_listObj[OBJID::END];
	list<CObj*>				m_listMapBLOCK[MAPBLOCK::END];
	list<CObj*>				m_listItem[GAMEITEM::END];
	static CObjManager* m_pInstance;

	bool					m_bisBombPlayerCollid;
	int						m_iStage1Clear;
	int						m_BossHP;

	bool					m_bisCheat;

	vector<int>				m_vecDeadTileKey;
	vector<int>				m_vecItemKey;
	vector<ITEMINFO>		m_vecItem;
	vector<int>				m_vecDeadBlockKey;
};


#endif // !__OBJMANAGER_H__