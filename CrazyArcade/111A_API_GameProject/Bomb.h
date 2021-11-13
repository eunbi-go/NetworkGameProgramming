#pragma once

#ifndef __BOMB_H__
#define __BOMB_H__


#include "Obj.h"
class CBomb : public CObj
{
public:
	CBomb();
	virtual ~CBomb();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();


public:
	bool Get_isBombCollid() { return m_isCollidPlayer; }

	float Get_BombX() { return m_tInfo.fX; }
	float Get_BombY() { return m_tInfo.fY; }

public:
	void SetBombCollid(bool _iscollid) { m_isCollidPlayer = _iscollid; }
	void SetBombWaveStop(float _isStop) { m_Wavecnt = _isStop; }
	void SetBombPower(int _Bombpower) { m_tInfo.iBombPower = _Bombpower; }

	void SetRightBombPower(int _power) { iRightBombPower = _power; }
	void SetLeftBombPower(int _power) { iLeftBombPower = _power; }

private:
	DWORD			dBombTime;
	float			m_PlayerX;
	float			m_PlayerY;

	float			m_Wavecnt;


	bool			m_isCollidPlayer;
	list<CObj*>		m_listBlock[MAPBLOCK::END];

	int iRightBombPower;
	int iLeftBombPower;
	int iUpBombPower;
	int iDownBombPower;
};


#endif // !1__BOMB_H__