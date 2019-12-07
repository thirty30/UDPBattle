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
	cout << (n32)msgRecv.GetValue() << endl;

	PRegisterResp msgSend;
	msgSend.SetValue(55);
	this->SendToClient(S2C_REGISTER_RESP, a_nSID, msgSend);
}
