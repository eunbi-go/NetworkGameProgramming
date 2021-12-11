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
	const int Get_ClientID() const { return m_tInfo.iClientID; }
	const int Get_BombPower() const { return m_tInfo.iBombPower; }
	const int			Get_ObjNum() const { return m_nObjNum; }

	bool Get_Dead() { return m_tInfo.bisDead; }

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x, m_tInfo.fY = _y; }
	void Set_Dead() { m_tInfo.bisDead = true; }
	void SetBombPower(int _power) { m_tInfo.iBombPower = _power; }
	void SetState(OBJSTATE::STATE _State) { m_eState = _State; }
	void SetCurDIR(OBJDIR::DIR _Dir) { m_eCurDir = _Dir; }
	void SetPlayerDIR(OBJDIR::DIR _Dir) { m_tInfo.PlayerDir = _Dir; }
	void SetFrame(FRAME tFrame) { m_tFrame = tFrame; }
	void SetMonsterID(int iID) { m_tInfo.iMonsterID = iID; }

	void Set_PosX(float _x) { m_tInfo.fX += _x; }
	void Set_PosY(float _y) { m_tInfo.fY += _y; }
	void Change_PosX(float _x) { m_tInfo.fX = _x; }
	void Change_PosY(float _y) { m_tInfo.fY = _y; }
	void WaveAttack(int _att) { m_tInfo.iHP -= _att; }

	void Set_ClientID(int _id) { m_tInfo.iClientID = _id; }
	void Set_ObjNum(int _id) { m_nObjNum = _id; }

public:
	OBJSTATE::STATE GetState() { return m_eState; }

public:
	MAPBLOCK::BLOCK& Get_BlockType() { return m_eBlock; }



protected:
	INFO				m_tInfo;
	RECT				m_tRect;
	OBJSTATE::STATE		m_eState;
	OBJDIR::DIR			m_ePreDir;
	OBJDIR::DIR			m_eCurDir;

	FRAME				m_tFrame;

	DWORD				m_dwTime;

	MAPBLOCK::BLOCK		m_eBlock;

	int					m_nObjNum;
};


#endif // !__OBJ_H__