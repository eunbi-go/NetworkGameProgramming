#pragma once

#ifndef __LEAF1_H__
#define __LEAF1_H__

#include "Obj.h"
class CLeaf1 : public CObj
{
public:
	CLeaf1();
	virtual ~CLeaf1();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__LEAF1_H__
