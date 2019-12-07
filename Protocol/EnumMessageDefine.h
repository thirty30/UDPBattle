#pragma once

DEF_MSG_START(EMessageID)

	//create account
	DEF_C2S_ITEM(C2S_REGISTER)
	DEF_S2C_ITEM(S2C_REGISTER_RESP)

	DEF_MSG_ITEM(MSG_END)	//add message id above this

DEF_MSG_END



