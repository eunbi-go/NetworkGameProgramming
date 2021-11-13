#pragma once

#ifndef __LINEMANAGER_H__
#define __LINEMANAGER_H__

class CLine;
class CLineManager
{
public:
	CLineManager();
	~CLineManager();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

	bool CollisionLine(float _x, float* _y);

public:
	static CLineManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	list<CLine*>			m_ListLine;
	static CLineManager*	m_pInstance;
};


#endif // !__LINEMANAGER_H__
