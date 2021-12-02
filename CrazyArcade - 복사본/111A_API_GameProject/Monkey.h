#pragma once

#ifndef __MONKEY_H__
#define __MONKEY_H__


#include "Monster.h"
class CMonkey : public CMonster
{
public:
	CMonkey();
	virtual ~CMonkey();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();
};


#endif // !__MONKEY_H__