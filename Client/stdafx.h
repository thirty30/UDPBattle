#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>

#include "../TCore/TCore.h"
#include "../TMuffin/TMuffin.h"
#include "../Protocol/TProtocol.h"
#include "./CommonDefine.h"
#include "./ResourceManager/CResourceManager.h"
#include "./Control/CControl.h"
#include "./Control/CCameraControl.h"
#include "./Control/CShipControl.h"
#include "./Actor/CActor.h"
#include "./Actor/CBullet.h"
#include "./Scene/CScene.h"

////////////////////////////////////
//add include above the CGame.h
#include "./Game/CGame.h"

