#pragma once

#ifndef __WATINGROOM_H__
#define __WATINGROOM_H__

#include "Scene.h"
class CWatingRoom : public CScene
{
public:
	CWatingRoom();
	virtual ~CWatingRoom();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;



protected:
	void Update_Rect();

private:


	INFO				m_tInfo;
	RECT				m_tRect;


};


#endif // !__WATINGROOM_H__
