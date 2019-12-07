MESSAGE_HEAD( MessageN8 )
MSG_ITEM( N8,	Value )
MESSAGE_TAIL( MessageN8 )

MESSAGE_HEAD( MessageU8 )
MSG_ITEM( U8,	Value )
MESSAGE_TAIL( MessageU8 )

MESSAGE_HEAD( MessageN16 )
MSG_ITEM( N16,	Value )
MESSAGE_TAIL( MessageN16 )

MESSAGE_HEAD( MessageU16 )
MSG_ITEM( U16,	Value )
MESSAGE_TAIL( MessageU16 )

MESSAGE_HEAD( MessageN32 )
MSG_ITEM( N32,	Value )
MESSAGE_TAIL( MessageN32 )

MESSAGE_HEAD( MessageU32 )
MSG_ITEM( U32,	Value )
MESSAGE_TAIL( MessageU32 )

MESSAGE_HEAD( MessageN64 )
MSG_ITEM( N64,	Value )
MESSAGE_TAIL( MessageN64 )

MESSAGE_HEAD( MessageU64 )
MSG_ITEM( U64,	Value )
MESSAGE_TAIL( MessageU64 )

MESSAGE_HEAD( MessageF32 )
MSG_ITEM( F32,	Value )
MESSAGE_TAIL( MessageF32 )

MESSAGE_HEAD( MessageF64 )
MSG_ITEM( F64,	Value )
MESSAGE_TAIL( MessageF64 )

MESSAGE_HEAD( MessageStr )
MSG_ITEM( STR,	Value )
MESSAGE_TAIL( MessageStr )

//Register
MESSAGE_HEAD(Register)
MSG_ITEM(STR, Email)
MSG_ITEM(STR, Password)
MESSAGE_TAIL(Register)

//Authenticate
MESSAGE_HEAD(Authenticate)
MSG_ITEM(STR, Email)
MSG_ITEM(STR, Password)
MESSAGE_TAIL(Authenticate)

//RoomInfo
MESSAGE_HEAD(RoomInfo)
MSG_ITEM(N32, RoomID)
MSG_ITEM(STR, RoomName)
MSG_ITEM(N32, MemberNum)
MESSAGE_TAIL(RoomInfo)

//Room list
MESSAGE_HEAD(RoomList)
MSG_ITEM(N8, ResultCode)
MSG_ITEM(N32, UserID)
MSG_ITEM(N32, CreationDate)
MSG_ITEM(ARRAY, RoomInfo)
MESSAGE_TAIL(RoomList)

//Broadcast
MESSAGE_HEAD(Broadcast)
MSG_ITEM(N16, Type)
MSG_ITEM(STR, UserName)
MSG_ITEM(STR, RoomName)
MSG_ITEM(STR, Content)
MESSAGE_TAIL(Broadcast)

//chat message
MESSAGE_HEAD(ChatMessage)
MSG_ITEM(N32, RoomID)
MSG_ITEM(STR, Content)
MESSAGE_TAIL(ChatMessage)

