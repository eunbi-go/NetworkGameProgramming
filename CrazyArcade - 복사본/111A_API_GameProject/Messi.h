#pragma once

#ifndef __MESSI_H__
#define __MESSI_H__

#include "Obj.h"
class CMessi : public CObj
{
public:
	CMessi();
	virtual ~CMessi();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__MESSI_H__
