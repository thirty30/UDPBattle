#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <time.h>
using namespace std;

#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#include <io.h>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>

#include "../TCore/TCore.h"
#include "../Protocol/TProtocol.h"
#include "../Protocol/ConstantDefine.h"
#include "./CommonDefine.h"
#include "./Server/CSession.h"
#include "./Battle/CPlayer.h"
#include "./Battle/CBattle.h"
#include "./Server/CServer.h"


