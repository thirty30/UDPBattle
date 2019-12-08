typedef void (CServer::*Handler)(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pMsgBase, u32 a_uSize);
Handler m_HandlerTable[MSG_END];

tbool InitMessageHandler()
{
	#define SET_HANDLER_TABLE( MsgID, Func ) m_HandlerTable[ MsgID ] = &CServer::Func;

	SET_HANDLER_TABLE(C2S_REGISTER, HandlerRegister);
	SET_HANDLER_TABLE(C2S_PLAYER_ACTION, HandlerPlayerAction);


#undef SET_HANDLER_TABLE
	return true;
}

void HandlerRegister(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pMsgBase, u32 a_uSize);
void HandlerPlayerAction(u32 a_uMsgID, u64 a_nSID, const tcchar* a_pMsgBase, u32 a_uSize);


