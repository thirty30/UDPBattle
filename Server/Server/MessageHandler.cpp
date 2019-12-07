#include "stdafx.h"

#define READ_CLIENT_MESSAGE(MsgID, Msg)	\
Msg msgRecv;	\
msgRecv.Deserialize(a_pMsgBase, a_uSize); \
CSession* pSession = this->GetSession(a_nFD); \
if (pSession == NULL) \
{ \
	return; \
}

void CServer::HandlerCreateAccount(u32 a_uMsgID, socketfd a_nFD, const tcchar* a_pMsgBase, u32 a_uSize)
{
	READ_CLIENT_MESSAGE(a_uMsgID, PRegister);
	string strEmail = string(msgRecv.GetEmail(), msgRecv.GetEmailSize());
	string strPassword = string(msgRecv.GetPassword(), msgRecv.GetPasswordSize());
}
