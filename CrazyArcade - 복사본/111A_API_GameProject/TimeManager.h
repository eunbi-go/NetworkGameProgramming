#pragma once
class CTimeManager
{
private:
	CTimeManager();
	~CTimeManager();

public:
	HRESULT Ready_CTimeManager();
	void Update_CTimeManager();

public:
	double Get_DeltaTime() { return m_dDeltaTime; }


public:
	static CTimeManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTimeManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CTimeManager*	m_pInstance;
	LARGE_INTEGER			m_CpuTick;
	LARGE_INTEGER			m_PreTime;
	LARGE_INTEGER			m_CurTime;
	double					m_dDeltaTime;
};

