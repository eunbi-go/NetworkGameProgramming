#pragma once

#ifndef __ROCK3_H__
#define __ROCK3_H__

#include "Obj.h"
class Rock3 : public CObj
{
public:
	Rock3();
	virtual ~Rock3();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__ROCK3_H__
