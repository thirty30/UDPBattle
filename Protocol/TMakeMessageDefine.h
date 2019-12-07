#pragma once

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
#undef MESSAGE_HEAD
#undef MSG_ITEM
#undef MESSAGE_TAIL
#undef TYPEDEF_MESSAGE


//////////////////////////////////////////////////////////////////////////

#define MSG_ITEM_NORMAL(TypeClass, Variable) \
	TypeClass m_##Variable;	\
	void Set##Variable(TypeClass::Type a_value) { m_##Variable.m_value = a_value; }	\
	const TypeClass::Type& Get##Variable() const { return m_##Variable.m_value;}


#define MSG_ITEM_BINARY(TypeClass, Variable) \
	TypeClass m_##Variable;	\
	void Set##Variable(const tcchar* a_pData, u32 a_uSize) { m_##Variable.m_uSize = a_uSize; m_##Variable.m_pData = a_pData; } \
	void Alloc##Variable(const tcchar* a_pData, n32 a_uSize) { \
		m_##Variable.m_uSize = a_uSize; \
		tcchar* pTemp = RequireMessageHeap(a_uSize); \
		if(pTemp == NULL) { return; } \
		TMemcpy(pTemp, a_uSize, a_pData, a_uSize); \
		m_##Variable.m_pData = pTemp; \
	} \
	const tcchar* Get##Variable() const { return m_##Variable.m_pData; } \
	n32 Get##Variable##Size() const { return m_##Variable.m_uSize; } 


#define MSG_ITEM_ARRAY(TypeClass, Variable) \
	PMsgTypeN32 m_##Variable##Count; \
	P##Variable* m_##Variable; \
	P##Variable* m_##Variable##Tail; \
	void Alloc##Variable(n32 a_nCount) { \
		m_##Variable##Count.m_value = a_nCount; \
		tcchar* pAddress = RequireMessageHeap(a_nCount * sizeof(P##Variable)); \
		m_##Variable = new(pAddress) P##Variable[a_nCount];	\
		for (n32 i = 0; i < a_nCount; i++) \
		{ \
			m_##Variable##Tail = m_##Variable + i; \
			if(i + 1 < a_nCount) { m_##Variable##Tail->m_pNext = m_##Variable + i + 1; } \
		} \
		m_##Variable##Tail->m_pNext = NULL; \
	} \
	const P##Variable* Get##Variable##At(n32 a_nIndex) const \
	{ \
		if (a_nIndex >= m_##Variable##Count.m_value) \
		{ \
			return NULL; \
		} \
		const P##Variable* pTarget = m_##Variable; \
		for (n32 i = 0; i < a_nIndex; i++) \
		{ \
			pTarget = pTarget->m_pNext; \
		} \
		return pTarget;	\
	} \
	n32 Get##Variable##Count() const { return m_##Variable##Count.m_value; } \
	P##Variable* Mutable##Variable##At(n32 a_nIndex) \
	{ \
		if (a_nIndex >= m_##Variable##Count.m_value) \
		{ \
			return NULL; \
		} \
		P##Variable* pTarget = m_##Variable; \
		for (n32 i = 0; i < a_nIndex; i++) \
		{ \
			pTarget = pTarget->m_pNext; \
		} \
		return pTarget; \
	} \
	P##Variable* append##Variable()	\
	{ \
		tcchar* pAddress = RequireMessageHeap(sizeof(P##Variable)); \
		P##Variable* pTemp = new(pAddress) P##Variable(); \
		if (m_##Variable##Count.m_value == 0) \
		{ \
			m_##Variable = pTemp; \
			m_##Variable##Tail = pTemp; \
			m_##Variable##Tail->m_pNext = NULL; \
		} \
		else \
		{ \
			m_##Variable##Tail->m_pNext = pTemp; \
			m_##Variable##Tail = pTemp; \
			m_##Variable##Tail->m_pNext = NULL; \
		} \
		m_##Variable##Count.m_value += 1; \
		return pTemp; \
	}

#define MSG_ITEM_STRUCT(TypeClass, Variable) \
	P##Variable m_##Variable; \
	const P##Variable& Get##Variable() const { return m_##Variable; } \
	P##Variable& Mutable##Variable() { return m_##Variable; }


#define MSG_ITEM_N8		MSG_ITEM_NORMAL
#define MSG_ITEM_U8		MSG_ITEM_NORMAL
#define MSG_ITEM_N16	MSG_ITEM_NORMAL
#define MSG_ITEM_U16	MSG_ITEM_NORMAL
#define MSG_ITEM_N32	MSG_ITEM_NORMAL
#define MSG_ITEM_U32	MSG_ITEM_NORMAL
#define MSG_ITEM_N64	MSG_ITEM_NORMAL
#define MSG_ITEM_U64	MSG_ITEM_NORMAL
#define MSG_ITEM_F32	MSG_ITEM_NORMAL
#define MSG_ITEM_F64	MSG_ITEM_NORMAL
#define MSG_ITEM_STR	MSG_ITEM_BINARY
#define MSG_ITEM_BLOB	MSG_ITEM_BINARY


#define MESSAGE_HEAD(ClassName) \
class P##ClassName : public PMessageBase \
{ \
public: \
	P##ClassName* m_pNext; \
	P##ClassName () : m_pNext(NULL) {}; \
	~P##ClassName () {}; \
	virtual u32 Serialize(tcchar* a_pData, u32 a_uLimit) const; \
	virtual u32 Deserialize(const tcchar* a_pData, u32 a_uLimit); \
	virtual u32 GetLength() const;
#define MSG_ITEM(T, Variable)	MSG_ITEM_##T(PMsgType##T, Variable)
#define MESSAGE_TAIL(ClassName) \
};

#define TYPEDEF_MESSAGE(SRC, NEW) typedef P##SRC P##NEW;

