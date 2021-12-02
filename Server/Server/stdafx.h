#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "enum.h"
#include "struct.h"
#include "define.h"
#include "Function.h"
#include "AbstractFactory.h"

using namespace std;

#define SERVERPORT	9000
#define BUFSIZE		512

#define MAPSTARTX 20
#define MAPSTARTY 40

#define TILECX 40
#define TILECY 40