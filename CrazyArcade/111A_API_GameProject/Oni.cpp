#include "stdafx.h"
#include "Oni.h"


COni::COni()
{
}


COni::~COni()
{
	Release();
}

void COni::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_tInfo.fSpeed = 1.f;

	m_tInfo.iHP = 5;
	m_tInfo.iAttack = 1;

	m_tInfo.bisDead = false;
}

int COni::Update()
{
	if (m_tInfo.iHP <= 0)
		m_tInfo.bisDead = true;

	if (m_tInfo.bisDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_tInfo.fSpeed;


	Update_Rect();
	return OBJ_NOEVENET;
}

void COni::Late_Update()
{

	
}

void COni::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, myBrush);

	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(_DC, oldBrush);
	DeleteObject(myBrush);
}

void COni::Release()
{
}
