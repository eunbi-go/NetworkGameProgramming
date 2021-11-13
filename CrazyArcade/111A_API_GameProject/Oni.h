#pragma once

#ifndef __ONI_H__
#define __ONI_H__


#include "Monster.h"
class COni : public CMonster
{
public:
	COni();
	virtual ~COni();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();
};


#endif // !1
