#include "stdafx.h"
#include "Tile.h"

CTile::CTile()
	: m_iTilekey(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Release()
{
}
