#pragma once

#ifndef __GRASS_H__
#define __GRASS_H__

#include "Obj.h"
class CGrass : public CObj
{
public:
	CGrass();
	virtual ~CGrass();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__GRASS_H__
