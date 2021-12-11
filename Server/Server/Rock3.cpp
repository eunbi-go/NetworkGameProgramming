#include "stdafx.h"
#include "Rock3.h"
//#include "BmpManager.h"
//#include "KeyManager.h"
#include "TileManager.h"

Rock3::Rock3()
{
}


Rock3::~Rock3()
{
	Release();
}

void Rock3::Initialize()
{
	m_eBlock = MAPBLOCK::ROCK3;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;
}

int Rock3::Update()
{
	Update_Rect();
	return OBJ_NOEVENET;
}

void Rock3::Late_Update()
{
}

void Rock3::Render(HDC _DC)
{
}

void Rock3::Release()
{
}
