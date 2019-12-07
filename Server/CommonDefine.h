#pragma once

typedef SOCKET socketfd;

#define LISTEN_PORT 9988
#define SERVER_RECEIVE_BUFFER_SIZE 1024*1024


#define MAX_SEND_HEAP_LENGTH 1024*1024*8	//send message buffer size
#define SERVER_SEND_BUFFER_SIZE 1024*1024


#define USER_NAME_LEN 128

#define CHAT_ROOM_MEMBER_NUM 64
#define CHAT_ROOM_NAME_LEN 128
#define CHAT_ROOM_NUM 3


T_INLINE u64 CalcSessionID(sockaddr_in& a_rClient)
{
	u32 nIP = a_rClient.sin_addr.S_un.S_addr;
	u16 nPort = a_rClient.sin_port;
	return (nIP << 16 + nPort);
}

