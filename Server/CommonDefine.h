#pragma once

#define LISTEN_PORT 9988
#define SERVER_RECEIVE_BUFFER_SIZE 1024*1024*5
#define SERVER_SEND_BUFFER_SIZE 1024*1024*5
#define MAX_SEND_HEAP_LENGTH 1024*1024*8	//send message buffer size

enum EPlayerState
{
	E_PLAYER_STATE_BOT = 0,
	E_PLAYER_STATE_PLAYER,
	E_PLAYER_STATE_DEAD,
};

#define SCENE_LENGTH 150
#define SCENE_WIDTH 80

#define RESURGENCE_TIME 5.0f
#define PLAYER_VELOCITY 50.0f
#define PLAYER_ROTATION_VELOCITY 50.0f
#define BULLET_VELOCITY 200.0f
#define BULLET_LIFE_TIME 2.0f
#define BULLET_HIT_RADIUS 5.0f

#define ACTION_FRONT 1
#define ACTION_BACK 2
#define ACTION_LEFT 4
#define ACTION_RIGHT 8

T_INLINE u64 CalcSessionID(sockaddr_in& a_rClient)
{
	u32 nIP = a_rClient.sin_addr.S_un.S_addr;
	u16 nPort = a_rClient.sin_port;
	return (nIP << 16 + nPort);
}

T_INLINE glm::vec3 RandPosition()
{
	f32 fX = TRandInRange(-SCENE_LENGTH, SCENE_LENGTH);
	f32 fZ = TRandInRange(-SCENE_LENGTH, SCENE_LENGTH);
	return glm::vec3(fX, 0.0f, fZ);
}

