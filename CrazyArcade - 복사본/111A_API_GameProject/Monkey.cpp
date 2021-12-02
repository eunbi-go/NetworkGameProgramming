#include "stdafx.h"
#include "Monkey.h"


CMonkey::CMonkey()
{
}


CMonkey::~CMonkey()
{
	Release();
}

void CMonkey::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_tInfo.fSpeed = 1.f;

	m_tInfo.iHP = 5;
	m_tInfo.iAttack = 1;

	m_tInfo.bisDead = false;
}

int CMonkey::Update()
{
	if (m_tInfo.iHP <= 0)
		m_tInfo.bisDead = true;

	if (m_tInfo.bisDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_tInfo.fSpeed;


	Update_Rect();
	return OBJ_NOEVENET;
}

void CMonkey::Late_Update()
{
}

void CMonkey::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, myBrush);

	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(_DC, oldBrush);
	DeleteObject(myBrush);
}

void CMonkey::Release()
{
}
