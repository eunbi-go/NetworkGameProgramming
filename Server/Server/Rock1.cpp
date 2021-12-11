#include "stdafx.h"
#include "Rock1.h"
//#include "BmpManager.h"
//#include "KeyManager.h"
#include "TileManager.h"

Rock1::Rock1()
{
}


Rock1::~Rock1()
{
	Release();
}

void Rock1::Initialize()
{
	m_eBlock = MAPBLOCK::ROCK1;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;
}

int Rock1::Update()
{
	Update_Rect();
	return OBJ_NOEVENET;
}

void Rock1::Late_Update()
{
}

void Rock1::Render(HDC _DC)
{
}

void Rock1::Release()
{
}
