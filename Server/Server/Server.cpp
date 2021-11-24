#include "stdafx.h"
#include "TileManager.h"
#include "Obj.h"

static int iClientID = 0;				// 클라이언트의 ID
map<int, CLIENTINFO> WorldInfo;			// 클라이언트로 보낼 패킷
vector<CObj*>	vecMapTile;				// 맵 타일
vector<USHORT> vecIsFirstConnect;		// 클라이언트가 접속하면 클라이언트의 포트번호를 저장함 (처음 접속인지 확인용)

#define SERVERPORT 9000

void Receive_Data(LPVOID arg, map<int, ClientInfo> _worldInfo);
void Send_Data(LPVOID arg);
void Send_InitMap(LPVOID arg);

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL
	);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL
	);
	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char* buf, int len, int flags)
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

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

	// 현재 클라이언트가 처음 접속했는지 확인
	auto iter = find(vecIsFirstConnect.begin(), vecIsFirstConnect.end(), clientaddr.sin_port);
	if (iter == vecIsFirstConnect.end())
	{
		// 처음 접속이면 포트 번호를 저장
		vecIsFirstConnect.push_back(clientaddr.sin_port);
		// ClientID 보내기 (후에 처음 들어왔을때만 보내게 처리)
		retval = send(client_sock, (char*)&iClientID, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}

		int	iSize = sizeof(vecMapTile);

		retval = send(client_sock, (char*)&iSize, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}

		retval = send(client_sock, (char*)&vecMapTile, sizeof(iSize), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}

		Receive_Data((LPVOID)client_sock, WorldInfo);

		// 캐릭터 종류, 초기 위치 정해서 Client로 전송
		Send_Data((LPVOID)client_sock);

		// 맵 정보 전송 -> 클라이언트는 이 정보를 바탕으로 맵 초기화
		//Send_InitMap((LPVOID)client_sock);

		printf("포트 번호=%d 에게 ClientID: %d 전송 성공\n", ntohs(clientaddr.sin_port), iClientID);
		iClientID++;		// 다음 접속할 클라이언트 ID는 +1 해서 관리

	}
	else
	{
		//while (1) {
		//	
		//}
	}

	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char* argv[])
{
	int retval;

	// 맵 생성
	CTileManager::Get_Instance()->Load_Tile();
	vecMapTile = CTileManager::Get_Instance()->Get_MapTile();

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	while (1)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// 스레드 생성
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;

}

void Receive_Data(LPVOID arg, map<int, ClientInfo> _worldInfo)
{
	// 연결된 클라이언트로부터 각 플레이어의 ClientInfo를 받는다.
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	CLIENTINFO ClientInfo;

	// 고정 길이 데이터 받아오기
	retval = recvn(client_sock, (char*)&ClientInfo, sizeof(CLIENTINFO), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
	}

	// WorldInfo의 ClientID 키값에 ClientInfo를 저장한다.
	WorldInfo.insert({ iClientID, ClientInfo });
}

void Send_Data(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;

	// ClientID = 0,	위치는 왼쪽 위
	if (WorldInfo.find(0) != WorldInfo.end()) {
		WorldInfo[0].PlayerInfo.PlayerPos.fX = MAPSTARTX + (TILECX >> 1);
		WorldInfo[0].PlayerInfo.PlayerPos.fY = MAPSTARTY + (TILECY >> 1);
	}

	// ClientID = 1,	위치는 오른쪽 위
	if (WorldInfo.find(1) != WorldInfo.end()) {
		WorldInfo[1].PlayerInfo.PlayerPos.fX = MAPSTARTX + (TILECX * 14) + (TILECX >> 1);
		WorldInfo[1].PlayerInfo.PlayerPos.fY = MAPSTARTY + (TILECY >> 1);
	}

	// ClientID = 2,	위치는 왼쪽 아래
	if (WorldInfo.find(2) != WorldInfo.end()) {
		WorldInfo[2].PlayerInfo.PlayerPos.fX = MAPSTARTX + (TILECX >> 1);
		WorldInfo[2].PlayerInfo.PlayerPos.fY = MAPSTARTY + (TILECY * 12) + (TILECY >> 1);
	}

	// ClientID = 3,	위치는 오른쪽 아래
	if (WorldInfo.find(3) != WorldInfo.end()) {
		WorldInfo[3].PlayerInfo.PlayerPos.fX = MAPSTARTX + (TILECX * 14) + (TILECX >> 1);
		WorldInfo[3].PlayerInfo.PlayerPos.fY = MAPSTARTY + (TILECY * 12) + (TILECY >> 1);
	}


	retval = send(client_sock, (char*)&WorldInfo, sizeof(WorldInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
}

void Send_InitMap(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;

	// 맵 타일에서 장애물들이 깨질 수 있으니 항상 같은 크기를 갖지 않는다
	// -> 고정-가변 전송 방식으로 전송
	
	int	iSize = sizeof(vecMapTile);

	retval = send(client_sock, (char*)&iSize, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	retval = send(client_sock, (char*)&vecMapTile, sizeof(iSize), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
}
