#pragma once

enum EPlayerState
{
	E_PLAYER_STATE_BOT = 0,
	E_PLAYER_STATE_PLAYER,
};

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

