#pragma once

#ifndef __FLOWER_H__
#define __FLOWER_H__

#include "Obj.h"
class CFlower : public CObj
{
public:
	CFlower();
	virtual ~CFlower();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__FLOWER_H__
