#include "stdafx.h"
#include "ClientManager.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000

CClientManager* CClientManager::m_pInstance = nullptr;

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
}

int CClientManager::connectToServer()
{
	// 윈속을 초기화한 후, 서버와 통신을 하기 위한 소켓을 생성하고 서버에게 접속을 요청하는 함수
	// 리턴값: retval - connect()의 리턴값

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket 생성
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	
	// connect() - 서버에 접속 요청
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	return retval;
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

void CClientManager::err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void CClientManager::err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
