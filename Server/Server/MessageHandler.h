typedef void (CServer::*Handler)(u32 a_uMsgID, socketfd a_nFD, const tcchar* a_pMsgBase, u32 a_uSize);
Handler m_HandlerTable[MSG_END];

tbool InitMessageHandler()
{
	#define SET_HANDLER_TABLE( MsgID, Func ) m_HandlerTable[ MsgID ] = &CServer::Func;

	SET_HANDLER_TABLE(C2S_REGISTER, HandlerCreateAccount);


#undef SET_HANDLER_TABLE
	return true;
}

void HandlerCreateAccount(u32 a_uMsgID, socketfd a_nFD, const tcchar* a_pMsgBase, u32 a_uSize);


