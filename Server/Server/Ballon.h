#pragma once

#ifndef __BALLON_H__
#define __BALLON_H__

#include "Obj.h"
class CBallon : public CObj
{
public:
	CBallon();
	virtual ~CBallon();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__BALLON_H__
