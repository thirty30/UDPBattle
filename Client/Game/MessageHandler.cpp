#include "stdafx.h"

void CGame::HandlerRegisterResp(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize)
{
	PRegisterResp msgRecv;
	msgRecv.Deserialize(a_pMsgData, a_uSize);
	cout << (n32)msgRecv.GetValue() << endl;
}
