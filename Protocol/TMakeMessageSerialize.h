#pragma once

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
#undef MESSAGE_HEAD
#undef MSG_ITEM
#undef MESSAGE_TAIL
#undef TYPEDEF_MESSAGE


#define MSG_SERIALIZE_NORMAL(Variable) \
	uOffset += m_##Variable.Serialize(a_pData + uOffset, a_uLimit - uOffset);

#define MSG_SERIALIZE_ARRAY(Variable) \
	uOffset += m_##Variable##Count.Serialize(a_pData + uOffset, a_uLimit - uOffset); \
	P##Variable* p##Variable##Target = m_##Variable; \
	for (n32 i = 0; i < m_##Variable##Count.m_value; i++) \
	{ \
		uOffset += p##Variable##Target->Serialize(a_pData + uOffset, a_uLimit - uOffset); \
		p##Variable##Target = p##Variable##Target->m_pNext; \
	}

#define MSG_SERIALIZE_STRUCT(Variable) \
	uOffset += m_##Variable.Serialize(a_pData + uOffset, a_uLimit - uOffset);	

#define MSG_SERIALIZE_N8	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_U8	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_N16	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_U16	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_N32	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_U32	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_N64	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_U64	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_F32	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_F64	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_STR	MSG_SERIALIZE_NORMAL
#define MSG_SERIALIZE_BLOB	MSG_SERIALIZE_NORMAL
#define TYPEDEF_MESSAGE(SRC, NEW)


#define MESSAGE_HEAD(ClassName) u32 T_INLINE P##ClassName::Serialize(tcchar* a_pData, u32 a_uLimit) const \
{ \
	u32 uOffset = 0;
#define MSG_ITEM(TypeClass, Variable) MSG_SERIALIZE_##TypeClass(Variable)
#define MESSAGE_TAIL(ClassName ) \
	return uOffset; \
}


