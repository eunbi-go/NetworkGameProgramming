#pragma once

#ifndef __STAGEMAP_H__
#define __STAGEMAP_H__


class CStageMap
{
public:
	CStageMap();
	~CStageMap();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

protected:
	void Update_Rect();

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x, m_tInfo.fY = _y; }
	void Set_Dead() { m_tInfo.bisDead = true; }

	void Set_PosX(float _x) { m_tInfo.fX += _x; }
	void Set_PosY(float _y) { m_tInfo.fY += _y; }

public:
	const RECT& Get_Rect() const { return m_tRect; }
	const INFO& Get_Info() const { return m_tInfo; }

protected:
	INFO	m_tInfo;
	RECT	m_tRect;
};


#endif // !__STAGEMAP_H__