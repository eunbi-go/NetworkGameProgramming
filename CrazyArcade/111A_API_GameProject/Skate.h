#pragma once

#ifndef __SKATE_H__
#define __SKATE_H__

#include "Obj.h"
class CSkate : public CObj
{
public:
	CSkate();
	virtual ~CSkate();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__SKATE_H__
