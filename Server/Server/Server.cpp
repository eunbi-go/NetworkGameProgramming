#include "stdafx.h"

static int iClientID = 0;				// 클라이언트의 ID
map<int, CLIENTINFO> WorldInfo;			// 클라이언트로 보낼 패킷
vector<USHORT> vecIsFirstConnect;		// 클라이언트가 접속하면 클라이언트의 포트번호를 저장함 (처음 접속인지 확인용)
map<int, bool> mapIsRecv;				// 클라이언트에서 데이터를 전송받았는지 판단하기 위한 맵
map<int, bool> mapIsCollision;			// 버프 판단을 위한 충돌 확인 맵

HANDLE hRecvEvent;		// 각 클라이언트와의 수신 결과를 알려주기 위한 이벤트
HANDLE hSendEvent;		// 각 클라이언트와의 송신 결과를 알려주기 위한 이벤트

#define SERVERPORT 9000

void Receive_Data(LPVOID arg, map<int, ClientInfo> _worldInfo);
void Send_Data(LPVOID arg);

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

		Receive_Data((LPVOID)client_sock, WorldInfo);

		// 캐릭터 종류, 초기 위치 정해서 Client로 전송
		Send_Data((LPVOID)client_sock);

		printf("포트 번호=%d 에게 ClientID: %d 전송 성공\n", ntohs(clientaddr.sin_port), iClientID);
		iClientID++;		// 다음 접속할 클라이언트 ID는 +1 해서 관리

	}
	else
	{
		while (1) {

		}
	}
	
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	return 0;
}

int main(int argc, char* argv[])
{
	int retval;

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

	// 이벤트 생성
	hRecvEvent = CreateEvent(NULL, FALSE, FALSE, NULL);	// 자동 리셋, 비신호
	if (hRecvEvent == NULL) return 1;

	hSendEvent = CreateEvent(NULL, FALSE, FALSE, NULL);	// 자동 리셋, 비신호
	if (hSendEvent == NULL) return 1;

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

		// mapIsReceive컨테이너에 ClientID를 key로 가진 bool변수를 false로 초기화 한 다음 삽입해준다.
		mapIsRecv.insert({ iClientID, false });
	}

	// 이벤트 제거
	CloseHandle(hRecvEvent);
	CloseHandle(hSendEvent);

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
	
	// 클라이언트로부터 수신이 끝나면 mapIsReceive컨테이너에 ClientID에 맞는 value를 true로 바꿔준다.
	mapIsRecv[iClientID] = true;

	// mapIsRecv 안의 모든 값이 true이면 Send 이벤트 신호 상태로 변경

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

	else
	{

	}
}

//void CheckBuff()
//{
//	// 모든 클라이언트에게 정보를 받은 후
//	// 모든 플레이어가 충돌했다면 PlayInfo 안의 b_isContactPlayer를 true로 설정
//	RECT rc = {};
//
//	for (auto Dst = WorldInfo.begin(); Dst != WorldInfo.end(); ++Dst)
//	{
//		rc = Dst->second.PlayerInfo.PlayerSize;
//
//		for (auto Src = WorldInfo.begin(); Src != WorldInfo.end(); ++Src)
//		{
//			
//		}
//	}
//
//}
