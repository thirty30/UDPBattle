#pragma once

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
#undef MESSAGE_HEAD
#undef MSG_ITEM
#undef MESSAGE_TAIL
#undef TYPEDEF_MESSAGE


#define MSG_DESERIALIZE_NORMAL(Variable) \
	uOffset += m_##Variable.Deserialize(a_pData + uOffset, a_uLimit - uOffset);

#define MSG_DESERIALIZE_BINARY(Variable) \
	u32 u##Variable = m_##Variable.Deserialize(a_pData + uOffset, a_uLimit - uOffset); \
	if (u##Variable == 0) \
	{ \
		return 0; \
	} \
	uOffset += u##Variable;

#define MSG_DESERIALIZE_ARRAY(Variable) \
	uOffset += m_##Variable##Count.Deserialize(a_pData + uOffset, a_uLimit - uOffset); \
	if (m_##Variable##Count.m_value > 0) \
	{ \
		tcchar* pAddress##Variable = RequireMessageHeap(  m_##Variable##Count.m_value * sizeof(P##Variable) ); \
		m_##Variable = new(pAddress##Variable) P##Variable[ m_##Variable##Count.m_value ]; \
		for (n32 i = 0; i < m_##Variable##Count.m_value; i++) \
		{ \
			n32 n##Variable = m_##Variable[i].Deserialize(a_pData + uOffset, a_uLimit - uOffset); \
			if (n##Variable < 0) \
				{ \
					return 0; \
				} \
				else \
				{ \
					m_##Variable##Tail = m_##Variable+i; \
					m_##Variable##Tail->m_pNext = m_##Variable+i+1; \
					uOffset += n##Variable; \
				} \
		} \
		m_##Variable##Tail->m_pNext = NULL; \
	}

#define MSG_DESERIALIZE_N8		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_U8		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_N16		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_U16		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_N32		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_U32		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_N64		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_U64		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_F32		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_F64		MSG_DESERIALIZE_NORMAL
#define MSG_DESERIALIZE_STR		MSG_DESERIALIZE_BINARY
#define MSG_DESERIALIZE_BLOB	MSG_DESERIALIZE_BINARY
#define MSG_DESERIALIZE_STRUCT 	MSG_DESERIALIZE_BINARY
#define TYPEDEF_MESSAGE(SRC, NEW)


#define MESSAGE_HEAD(ClassName) u32 T_INLINE P##ClassName::Deserialize(const tcchar* a_pData, u32 a_uLimit) \
{ \
	u32 uOffset = 0;
#define MSG_ITEM(TypeClass, Variable) MSG_DESERIALIZE_##TypeClass(Variable)
#define MESSAGE_TAIL(ClassName) \
	return uOffset; \
}


