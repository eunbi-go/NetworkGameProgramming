#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>

#include "enum.h"
#include "struct.h"

using namespace std;

#define SERVERPORT	9000
#define BUFSIZE		512

#define MAPSTARTX 20
#define MAPSTARTY 40

#define TILECX 40
#define TILECY 40