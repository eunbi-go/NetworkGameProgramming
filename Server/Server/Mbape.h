#pragma once

#ifndef __MBAPE_H_
#define __MBAPE_H_

#include "Obj.h"
class CMbape : public CObj
{
public:
	CMbape();
	virtual ~CMbape();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__MBAPE_H_
