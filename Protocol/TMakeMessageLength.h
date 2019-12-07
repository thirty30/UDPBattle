#pragma once

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


#define MSG_LENGTH_NORMAL(Variable) \
	uOffset += m_##Variable.GetLength();

#define MSG_LENGTH_ARRAY(Variable) \
	uOffset += m_##Variable##Count.GetLength(); \
	P##Variable* p##Variable##Target = m_##Variable; \
	for (n32 i = 0; i < m_##Variable##Count.m_value; i++) \
	{ \
		uOffset += p##Variable##Target->GetLength(); \
		p##Variable##Target = p##Variable##Target->m_pNext; \
	}

#define MSG_LENGTH_STRUCT(Variable) \
	uOffset += m_##Variable.GetLength();


#define MSG_LENGTH_N8		MSG_LENGTH_NORMAL
#define MSG_LENGTH_U8		MSG_LENGTH_NORMAL
#define MSG_LENGTH_N16		MSG_LENGTH_NORMAL
#define MSG_LENGTH_U16		MSG_LENGTH_NORMAL
#define MSG_LENGTH_N32		MSG_LENGTH_NORMAL
#define MSG_LENGTH_U32		MSG_LENGTH_NORMAL
#define MSG_LENGTH_N64		MSG_LENGTH_NORMAL
#define MSG_LENGTH_U64		MSG_LENGTH_NORMAL
#define MSG_LENGTH_F32		MSG_LENGTH_NORMAL
#define MSG_LENGTH_F64		MSG_LENGTH_NORMAL
#define MSG_LENGTH_BLOB		MSG_LENGTH_NORMAL
#define MSG_LENGTH_STR		MSG_LENGTH_NORMAL
#define TYPEDEF_MESSAGE(SRC, NEW)


#define MESSAGE_HEAD(ClassName) u32 T_INLINE P##ClassName::GetLength() const \
{ \
	u32 uOffset = 0;
#define MSG_ITEM(TypeClass, Variable) MSG_LENGTH_##TypeClass(Variable)
#define MESSAGE_TAIL( ClassName ) \
	return uOffset; \
}

