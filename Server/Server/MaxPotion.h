#pragma once

#ifndef __MAXPOTION_H__
#define __MAXPOTION_H__

#include "Obj.h"
class CMaxPotion : public CObj
{
public:
	CMaxPotion();
	virtual ~CMaxPotion();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__MAXPOTION_H__
