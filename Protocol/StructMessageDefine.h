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
MSG_ITEM( N8,	Value )
MESSAGE_TAIL(Register)

MESSAGE_HEAD( RegisterResp )
MSG_ITEM( N8,	Value )
MESSAGE_TAIL( RegisterResp )

//Sync Actor State
MESSAGE_HEAD(PlayerState)
MSG_ITEM( STR,	Value )
MESSAGE_TAIL(PlayerState)

MESSAGE_HEAD(BulletState)
MSG_ITEM( STR,	Value )
MESSAGE_TAIL(BulletState)

MESSAGE_HEAD(PlayerStateList)
MSG_ITEM( ARRAY, PlayerState)
MSG_ITEM( ARRAY, BulletState)
MESSAGE_TAIL(PlayerStateList)

MESSAGE_HEAD(PlayerAction)
MSG_ITEM( N8,	Action )
MSG_ITEM( F32,	X )
MSG_ITEM( F32,	Z )
MSG_ITEM( F32,	RY )
MSG_ITEM( F32,	RW )
MSG_ITEM( F32,	TX )
MSG_ITEM( F32,	TZ )
MESSAGE_TAIL(PlayerAction)



