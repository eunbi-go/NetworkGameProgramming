# NetworkGameProgramming 텀 프로젝트  

[NetworkGame Programming] 3인 개발  

1) 개발 기간: 2021.11.13 ~ 2021.12.08  

2) 개발 환경: VisualStudio2019, C++, STL, TCP/IP, SourceTree  

3) 목표: TCP/IP 모델을 활용한 네트워크 환경 개발  

4) 담당:  
데이터 송수신: SendInfo(), ReceiveInfo()  
동기화: 맵, 블록, 아이템  

5) 관련 소스코드  
- 데이터 송수신하며 맵 블록, 아이템 동기화:  
CrazyArcade / 98.Manager / 09.ClientManager / ClientManager.cpp 내 sendInfo(), recvInfo()

Server / server.cpp 내 Send_Data()  

Server / server.cpp 내 Receive_Data()  


- 맵 초기화:  
CrazyArcade / 98.Manager / 09.ClinetManager / ClientManager.cpp 내 recvInitMapTile()

Server / server.cpp 내 Send_InitMap()
