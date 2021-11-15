#include "stdafx.h"
#include "ClientManager.h"

CClientManager* CClientManager::m_pInstance = nullptr;

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
}

int CClientManager::connectToServer()
{
	return 0;
}

void CClientManager::recvClientID()
{
}

int CClientManager::sendInfo()
{
	return 0;
}

int CClientManager::recvInfo()
{
	return 0;
}

void CClientManager::applyInfo()
{
}

void CClientManager::set_buffOn()
{
}
