#pragma once

#ifndef __TILE_H__
#define __TILE_H__

#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void Initialize() { };
	virtual int Update() { return 0; };
	virtual void Late_Update() { };
	virtual void Render(HDC _DC) { };

public:
	virtual void Release() override;

public:
	void Set_TileKey(int _TileKey) { m_iTilekey = _TileKey; }

public:
	const int& Get_TileKey() const { return m_iTilekey; }

public:
	void SetTileType(MAPBLOCK::BLOCK _tiletype) { m_eBlock = _tiletype; }

public:
	MAPBLOCK::BLOCK GetTileType() { return m_eBlock; }

private:
	int					m_iTilekey;


};


#endif // !__TILE_H__
