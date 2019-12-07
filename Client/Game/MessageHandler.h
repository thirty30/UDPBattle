typedef void (CGame::*Handler)(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize);
Handler m_HandlerTable[MSG_END];

tbool InitMessageHandler()
{
	#define SET_HANDLER_TABLE( MsgID, Func ) m_HandlerTable[ MsgID ] = &CGame::Func;

	SET_HANDLER_TABLE(C2S_REGISTER, HandlerRegister);


#undef SET_HANDLER_TABLE
	return true;
}

void HandlerRegister(u32 a_uMsgID, const tcchar* a_pMsgData, u32 a_uSize);


