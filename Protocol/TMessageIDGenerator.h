#pragma once

#define DEF_MSG_START( Enum )  enum Enum {
#define DEF_MSG_ITEM( Item )   Item ,
#define DEF_C2S_ITEM( Item )   Item ,
#define DEF_S2C_ITEM( Item )   Item ,
#define DEF_MSG_END            };


#include "./EnumMessageDefine.h"


#undef DEF_MSG_START
#undef DEF_MSG_ITEM
#undef DEF_C2S_ITEM
#undef DEF_S2C_ITEM
#undef DEF_MSG_END

