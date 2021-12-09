#pragma once

#ifndef __BASKET_H__
#define __BASKET_H__

#include "Obj.h"
class CBasket : public CObj
{
public:
	CBasket();
	virtual ~CBasket();




public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;



};


#endif // !__BASKET_H__
