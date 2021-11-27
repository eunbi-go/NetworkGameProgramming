#include "stdafx.h"
#include "ClientManager.h"
#include "TileManager.h"
#include "ObjManager.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000

CClientManager* CClientManager::m_pInstance = nullptr;

CClientManager::CClientManager()
{
	ZeroMemory(&tClientInfo, sizeof(tClientInfo));

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
	retval = recvn(sock, (char*)&iClientID, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}

	
}

int CClientManager::sendInfo()
{
	// ClientID에 따라서 캐릭터를 정해서 서버로 보냄
	// ClientID : 0 -> 배찌,	ClientID : 1 -> 다오,	ClientID : 2 -> 디즈니

	switch (iClientID)
	{
	case 0:
		tClientInfo.PlayerInfo.PlayerName = CHARNAME::BAZZI;
		break;
	case 1:
		tClientInfo.PlayerInfo.PlayerName = CHARNAME::DAO;
		break;
	case 2:
		tClientInfo.PlayerInfo.PlayerName = CHARNAME::DIGENIE;
		break;
	default:
		tClientInfo.PlayerInfo.PlayerName = CHARNAME::UNI;
		break;
	}

	// 플레이어 위치 tClientInfo에 저장
	setPlayerInfo();

	// 서버에 잘 전송됐는지 시험해보기 위해 (성공 후 삭제할 것)
	retval = send(sock, (char*)&tClientInfo, sizeof(CLIENTINFO), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
	//int k = 10;
	//retval = send(sock, (char*)&k, sizeof(int), 0);
	//if (retval == SOCKET_ERROR) {
	//	err_display("send()");
	//}
	return retval;
}

int CClientManager::recvInfo()
{
	// 서버로부터 모든 클라이언트의 
	// 플레이어 정보, 아이템 정보, 몬스터 정보를 담고 있는 
	// WorldInfo 맵 컨테이너를 받는다.

	// 몇 개의 ClientInfo가 있는지 알아야 한다.
	//retval = recvn(sock, (char*)&tClientInfo, sizeof(CLIENTINFO), 0);
	//if (retval == SOCKET_ERROR) {
	//	err_display("recv()");
	//}
	int k = 0;
	retval = recvn(sock, (char*)&k, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}


	return retval;
}

void CClientManager::applyInfo()
{
}

void CClientManager::set_buffOn()
{
}

void CClientManager::recvInitPlayerPos()
{
	retval = recvn(sock, (char*)&tClientInfo, sizeof(CLIENTINFO), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}


}

void CClientManager::recvInitMapTile()
{
	// 고정 - 파일 이름 크기
	retval = recvn(sock, (char*)&iNameLen, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}
	
	char* pName = new char[iNameLen+1];

	// 가변 - 파일 이름
	retval = recvn(sock, &pName[0], iNameLen, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}
	pName[iNameLen] = '\0';


	retval = recvn(sock, (char*)&iFileSize, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}

	char* fileD = new char[iFileSize];

	retval = recvn(sock, &fileD[0], iFileSize, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}

	std::ofstream    out{ pName, std::ios::out };
	out.write(&fileD[0], iFileSize);

	strcat_s(buf, pName);
	CTileManager::Get_Instance()->Set_DataFile(buf, strlen(buf));
}

void CClientManager::setPlayerInfo()
{
	tClientInfo.PlayerInfo.PlayerPos.fX = CObjManager::Get_Instance()->Get_PlayerX();
	tClientInfo.PlayerInfo.PlayerPos.fY = CObjManager::Get_Instance()->Get_PlayerY();
	
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

int CClientManager::recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}
