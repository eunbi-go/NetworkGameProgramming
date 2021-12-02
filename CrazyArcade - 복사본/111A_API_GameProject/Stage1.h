#pragma once

#ifndef __STAGE1_H__
#define __STAGE1_H__

#include "Scene.h"
class CStage1 : public CScene
{
public:
	CStage1();
	virtual ~CStage1();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;



};


#endif // !__STAGE1_H__
