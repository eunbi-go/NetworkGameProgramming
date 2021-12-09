#include "stdafx.h"
#include "Rock2.h"
//#include "BmpManager.h"
//#include "KeyManager.h"
#include "TileManager.h"

Rock2::Rock2()
{
}


Rock2::~Rock2()
{
	Release();
}

void Rock2::Initialize()
{
	m_eBlock = MAPBLOCK::ROCK2;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;
}

int Rock2::Update()
{
	Update_Rect();
	return OBJ_NOEVENET;
}

void Rock2::Late_Update()
{
}

void Rock2::Render(HDC _DC)
{
}

void Rock2::Release()
{
}
