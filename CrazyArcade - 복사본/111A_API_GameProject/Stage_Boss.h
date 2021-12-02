#pragma once

#ifndef __STAGEBOSS_H_
#define __STAGEBOSS_H_

#include "Scene.h"
class CStage_Boss : public CScene
{
public:
	CStage_Boss();
	virtual ~CStage_Boss();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__STAGEBOSS_H_
