#pragma once

#ifndef __ROCK1_H__
#define __ROCK1_H__

#include "Obj.h"
class Rock1 : public CObj
{
public:
	Rock1();
	virtual ~Rock1();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__ROCK1_H__
