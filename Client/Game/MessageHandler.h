typedef void (CGame::*Handler)(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize);
Handler m_HandlerTable[MSG_END];

tbool InitMessageHandler()
{
	#define SET_HANDLER_TABLE( MsgID, Func ) m_HandlerTable[ MsgID ] = &CGame::Func;

	SET_HANDLER_TABLE(S2C_REGISTER_RESP, HandlerRegisterResp);


#undef SET_HANDLER_TABLE
	return true;
}

void HandlerRegisterResp(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize);


