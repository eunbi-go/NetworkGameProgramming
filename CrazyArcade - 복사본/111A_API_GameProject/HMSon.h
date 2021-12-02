#pragma once

#ifndef __HMSON_H__
#define __HMSON_H__

#include "Obj.h"
class CHMSon : public CObj
{
public:
	CHMSon();
	virtual ~CHMSon();

public:
	void Bomb_Drop();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	int		m_bossFrame;
};


#endif // !__HMSON_H__
