#pragma once

#ifndef __POTION_H__
#define __POTION_H__

#include "Obj.h"
class CPotion : public CObj
{
public:
	CPotion();
	virtual ~CPotion();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__POTION_H__
