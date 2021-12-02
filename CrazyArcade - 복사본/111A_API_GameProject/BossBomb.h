#pragma once

#ifndef __BOSSBOMB_H__
#define __BOSSBOMB_H__

#include "Obj.h"
class CBossBomb : public CObj
{
public:
	CBossBomb();
	virtual ~CBossBomb();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

private:
	DWORD			dBombTime;
};


#endif // !__BOSSBOMB_H__
