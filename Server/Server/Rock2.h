#pragma once

#ifndef __ROCK2_H__
#define __ROCK2_H__

#include "Obj.h"
class Rock2 : public CObj
{
public:
	Rock2();
	virtual ~Rock2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__ROCK2_H__
