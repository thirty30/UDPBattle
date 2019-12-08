#include "stdafx.h"

#define READ_CLIENT_MESSAGE(MsgID, Msg)	\
Msg msgRecv;	\
msgRecv.Deserialize(a_pMsgBase, a_uSize); \
CSession* pSession = this->FindSession(a_nSID); \
if (pSession == NULL) \
{ \
	return; \
}

void CServer::HandlerRegister(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pMsgBase, u32 a_uSize)
{
	READ_CLIENT_MESSAGE(a_uMsgID, PRegister);
	CBattle::GetSingleton().AddPlayer(pSession);
}

void CServer::HandlerPlayerAction(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pMsgBase, u32 a_uSize)
{
	READ_CLIENT_MESSAGE(a_uMsgID, PPlayerAction);
	CBattle::GetSingleton().PlayerAction(pSession, msgRecv.GetAction());
}
