#pragma once

#ifndef __SMALLMBAPE_H__
#define __SMALLMBAPE_H__


#include "Obj.h"
class SmallMbape : public CObj
{
public:
	SmallMbape();
	virtual ~SmallMbape();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__SMALLMBAPE_H__
