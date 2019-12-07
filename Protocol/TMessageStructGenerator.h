#pragma once

#include "./TMakeMessageDefine.h"
#include "./StructMessageDefine.h"

#include "./TMakeMessageSerialize.h"
#include "./StructMessageDefine.h"

#include "./TMakeMessageDeserialize.h"
#include "./StructMessageDefine.h"

#include "./TMakeMessageLength.h"
#include "./StructMessageDefine.h"

#undef MSG_ITEM_NORMAL
#undef MSG_ITEM_BINARY
#undef MSG_ITEM_ARRAY
#undef MSG_ITEM_STRUCT
#undef MSG_ITEM_N8	
#undef MSG_ITEM_U8	
#undef MSG_ITEM_N16
#undef MSG_ITEM_U16
#undef MSG_ITEM_N32
#undef MSG_ITEM_U32
#undef MSG_ITEM_N64
#undef MSG_ITEM_U64
#undef MSG_ITEM_F32
#undef MSG_ITEM_F64
#undef MSG_ITEM_STR
#undef MSG_ITEM_BLOB

#undef MSG_SERIALIZE_N8
#undef MSG_SERIALIZE_U8
#undef MSG_SERIALIZE_N16
#undef MSG_SERIALIZE_U16
#undef MSG_SERIALIZE_N32
#undef MSG_SERIALIZE_U32
#undef MSG_SERIALIZE_N64
#undef MSG_SERIALIZE_U64
#undef MSG_SERIALIZE_F32
#undef MSG_SERIALIZE_F64
#undef MSG_SERIALIZE_STR
#undef MSG_SERIALIZE_BLOB
#undef MSG_SERIALIZE_ARRAY
#undef MSG_SERIALIZE_STRUCT

#undef MSG_DESERIALIZE_N8
#undef MSG_DESERIALIZE_U8
#undef MSG_DESERIALIZE_N16
#undef MSG_DESERIALIZE_U16
#undef MSG_DESERIALIZE_N32
#undef MSG_DESERIALIZE_U32
#undef MSG_DESERIALIZE_N64
#undef MSG_DESERIALIZE_U64
#undef MSG_DESERIALIZE_F32
#undef MSG_DESERIALIZE_F64
#undef MSG_DESERIALIZE_STR
#undef MSG_DESERIALIZE_BLOB
#undef MSG_DESERIALIZE_STRUCT

#undef MSG_LENGTH_N8
#undef MSG_LENGTH_U8
#undef MSG_LENGTH_N16
#undef MSG_LENGTH_U16
#undef MSG_LENGTH_N32
#undef MSG_LENGTH_U32
#undef MSG_LENGTH_N64
#undef MSG_LENGTH_U64
#undef MSG_LENGTH_F32
#undef MSG_LENGTH_F64
#undef MSG_LENGTH_BLOB
#undef MSG_LENGTH_STR

#undef MESSAGE_HEAD
#undef MSG_ITEM
#undef MESSAGE_TAIL
#undef TYPEDEF_MESSAGE
