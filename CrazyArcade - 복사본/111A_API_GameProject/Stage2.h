#pragma once

#ifndef __STAGE2_H__
#define __STAGE2_H__

#include "Scene.h"
class CStage2 : public CScene
{
public:
	CStage2();
	virtual ~CStage2();


public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__STAGE2_H__
