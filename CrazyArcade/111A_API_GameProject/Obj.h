#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

protected:
	void Update_Rect();
	void Frame_Move();

public:
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x, m_tInfo.fY = _y; }
	void Set_Dead() { m_tInfo.bisDead = true; }
	void SetBombPower(int _power) { m_tInfo.iBombPower = _power; }
	void SetState(OBJSTATE::STATE _State) { m_eState = _State; }
	void SetCurDIR(OBJDIR::DIR _Dir) { m_eCurDir = _Dir; }

	void Set_PosX(float _x) { m_tInfo.fX += _x; }
	void Set_PosY(float _y) { m_tInfo.fY += _y; }
	void Change_PosX(float _x) { m_tInfo.fX = _x; }
	void Change_PosY(float _y) { m_tInfo.fY = _y; }
	void WaveAttack(int _att) { m_tInfo.iHP -= _att; }

public:
	OBJSTATE::STATE GetState() { return m_eState; }

public:
	MAPBLOCK::BLOCK& Get_BlockType()  { return m_eBlock; }



protected:
	INFO				m_tInfo;
	RECT				m_tRect;
	OBJSTATE::STATE		m_eState;
	OBJDIR::DIR			m_ePreDir;
	OBJDIR::DIR			m_eCurDir;

	FRAME				m_tFrame;

	DWORD				m_dwTime;

	MAPBLOCK::BLOCK		m_eBlock;


};


#endif // !__OBJ_H__