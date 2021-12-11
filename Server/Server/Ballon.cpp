#include "stdafx.h"
#include "Ballon.h"
//#include "BmpManager.h"

CBallon::CBallon()
{
}


CBallon::~CBallon()
{
	Release();
}

void CBallon::Initialize()
{

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 1000;
}

int CBallon::Update()
{
	if (m_tInfo.bisDead)
		return OBJ_DEAD;

	Update_Rect();
	Frame_Move();
	return OBJ_NOEVENET;
}

void CBallon::Late_Update()
{
}

void CBallon::Render(HDC _DC)
{
}

void CBallon::Release()
{
}
