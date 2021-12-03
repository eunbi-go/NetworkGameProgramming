#pragma once
#ifndef __NETWORKSTAGE_H__
#define __NETWORKSTAGE_H__

#include "Scene.h"
class CNetworkStage : public CScene
{
public:
	CNetworkStage();
	virtual ~CNetworkStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

#endif // !__NETWORKSTAGE_H__

