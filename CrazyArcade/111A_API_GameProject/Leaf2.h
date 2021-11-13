#pragma once

#ifndef __LEAF2_H__
#define __LEAF2_H__

#include "Obj.h"
class CLeaf2 : public CObj
{
public:
	CLeaf2();
	virtual ~CLeaf2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__LEAF2_H__
