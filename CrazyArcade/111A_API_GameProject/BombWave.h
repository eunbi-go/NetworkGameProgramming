#pragma once

#ifndef __BOMBWAVE_H__
#define __BOMBWAVE_H__

#include "Obj.h"
class CBombWave : public CObj
{
public:
	CBombWave();
	virtual ~CBombWave();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void Set_WaveDir(OBJDIR::DIR	_Dir) { m_eDir = _Dir; }
	void SetBombPower(int _Bombpower) { m_tInfo.iBombPower = _Bombpower; }


private:
	DWORD			dWaveTime;
	OBJDIR::DIR		m_eDir;

};


#endif // !__BOMBWAVE_H__
