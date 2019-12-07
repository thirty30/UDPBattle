#pragma once

#define CHECK_SERIALIZE_LENGTH \
	if (a_uLimit < sizeof(Type)) \
	{\
		return 0;\
	}
#define BINARY_TYPE_LENGTH 1024*65	

class PMsgTypeN8
{
public:
	typedef n8 Type;
	Type m_value;

	PMsgTypeN8()
		: m_value(0)
	{

	}
	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		*a_pData = m_value;
		return sizeof(Type);
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		m_value = *a_pData;
		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeU8
{
public:
	typedef u8 Type;
	Type m_value;

	PMsgTypeU8()
		: m_value(0)
	{

	}
	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		*a_pData = m_value;
		return sizeof(Type);
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		m_value = *a_pData;
		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeN16
{
public:
	typedef n16 Type;
	Type m_value;
	PMsgTypeN16()
		: m_value(0)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
#else
		a_pData[0] = pTarget[1];
		a_pData[1] = pTarget[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
#else
		pTarget[0] = a_pData[1];
		pTarget[1] = a_pData[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeU16
{
public:
	typedef u16 Type;
	Type m_value;
	PMsgTypeU16()
		: m_value(0)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
#else
		a_pData[0] = pTarget[1];
		a_pData[1] = pTarget[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
#else
		pTarget[0] = a_pData[1];
		pTarget[1] = a_pData[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeN32
{
public:
	typedef n32 Type;
	Type m_value;
	PMsgTypeN32()
		: m_value(0)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
		a_pData[2] = pTarget[2];
		a_pData[3] = pTarget[3];
#else
		a_pData[0] = pTarget[3];
		a_pData[1] = pTarget[2];
		a_pData[2] = pTarget[1];
		a_pData[3] = pTarget[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
		pTarget[2] = a_pData[2];
		pTarget[3] = a_pData[3];
#else
		pTarget[0] = a_pData[3];
		pTarget[1] = a_pData[2];
		pTarget[2] = a_pData[1];
		pTarget[3] = a_pData[0];
#endif
		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeU32
{
public:
	typedef u32 Type;
	Type m_value;
	PMsgTypeU32()
		: m_value(0)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
			tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
		a_pData[2] = pTarget[2];
		a_pData[3] = pTarget[3];
#else
		a_pData[0] = pTarget[3];
		a_pData[1] = pTarget[2];
		a_pData[2] = pTarget[1];
		a_pData[3] = pTarget[0];
#endif

		return sizeof(Type);
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
		pTarget[2] = a_pData[2];
		pTarget[3] = a_pData[3];
#else
		pTarget[0] = a_pData[3];
		pTarget[1] = a_pData[2];
		pTarget[2] = a_pData[1];
		pTarget[3] = a_pData[0];
#endif
		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeN64
{
public:
	typedef n64 Type;
	Type m_value;
	PMsgTypeN64()
		: m_value(0LL)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
		a_pData[2] = pTarget[2];
		a_pData[3] = pTarget[3];
		a_pData[4] = pTarget[4];
		a_pData[5] = pTarget[5];
		a_pData[6] = pTarget[6];
		a_pData[7] = pTarget[7];
#else
		a_pData[0] = pTarget[7];
		a_pData[1] = pTarget[6];
		a_pData[2] = pTarget[5];
		a_pData[3] = pTarget[4];
		a_pData[4] = pTarget[3];
		a_pData[5] = pTarget[2];
		a_pData[6] = pTarget[1];
		a_pData[7] = pTarget[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
		pTarget[2] = a_pData[2];
		pTarget[3] = a_pData[3];
		pTarget[4] = a_pData[4];
		pTarget[5] = a_pData[5];
		pTarget[6] = a_pData[6];
		pTarget[7] = a_pData[7];
#else
		pTarget[0] = a_pData[7];
		pTarget[1] = a_pData[6];
		pTarget[2] = a_pData[5];
		pTarget[3] = a_pData[4];
		pTarget[4] = a_pData[3];
		pTarget[5] = a_pData[2];
		pTarget[6] = a_pData[1];
		pTarget[7] = a_pData[0];
#endif
		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

class PMsgTypeU64
{
public:
	typedef u64 Type;
	Type m_value;

	PMsgTypeU64()
		: m_value(0)
	{

	}
	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
			tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
		a_pData[2] = pTarget[2];
		a_pData[3] = pTarget[3];
		a_pData[4] = pTarget[4];
		a_pData[5] = pTarget[5];
		a_pData[6] = pTarget[6];
		a_pData[7] = pTarget[7];
#else
		a_pData[0] = pTarget[7];
		a_pData[1] = pTarget[6];
		a_pData[2] = pTarget[5];
		a_pData[3] = pTarget[4];
		a_pData[4] = pTarget[3];
		a_pData[5] = pTarget[2];
		a_pData[6] = pTarget[1];
		a_pData[7] = pTarget[0];
#endif
		return sizeof(Type);
	}

	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
		pTarget[2] = a_pData[2];
		pTarget[3] = a_pData[3];
		pTarget[4] = a_pData[4];
		pTarget[5] = a_pData[5];
		pTarget[6] = a_pData[6];
		pTarget[7] = a_pData[7];
#else
		pTarget[0] = a_pData[7];
		pTarget[1] = a_pData[6];
		pTarget[2] = a_pData[5];
		pTarget[3] = a_pData[4];
		pTarget[4] = a_pData[3];
		pTarget[5] = a_pData[2];
		pTarget[6] = a_pData[1];
		pTarget[7] = a_pData[0];
#endif
		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};

//浮点数遵照IEEE标准，没有大小端问题
class PMsgTypeF32
{
public:
	typedef f32 Type;
	Type m_value;
	PMsgTypeF32()
		: m_value(0.0f)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		tcchar* pTarget = (tcchar*)&m_value;
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
		a_pData[2] = pTarget[2];
		a_pData[3] = pTarget[3];

		return sizeof(Type);
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
		pTarget[2] = a_pData[2];
		pTarget[3] = a_pData[3];

		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};


class PMsgTypeF64
{
public:
	typedef f64 Type;
	Type m_value;
	PMsgTypeF64()
		: m_value(0.0f)
	{

	}

	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		CHECK_SERIALIZE_LENGTH
		tcchar* pTarget = (tcchar*)&m_value;
		a_pData[0] = pTarget[0];
		a_pData[1] = pTarget[1];
		a_pData[2] = pTarget[2];
		a_pData[3] = pTarget[3];
		a_pData[4] = pTarget[4];
		a_pData[5] = pTarget[5];
		a_pData[6] = pTarget[6];
		a_pData[7] = pTarget[7];

		return sizeof(Type);
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		tcchar* pTarget = (tcchar*)&m_value;
		pTarget[0] = a_pData[0];
		pTarget[1] = a_pData[1];
		pTarget[2] = a_pData[2];
		pTarget[3] = a_pData[3];
		pTarget[4] = a_pData[4];
		pTarget[5] = a_pData[5];
		pTarget[6] = a_pData[6];
		pTarget[7] = a_pData[7];

		return sizeof(Type);
	}
	T_INLINE u32 GetLength() const
	{
		return sizeof(Type); 
	}
};



class PMsgTypeBinary
{
public:
	mutable u32 m_uCrc32;	//16 bit crc
	const tcchar* m_pData;	//数据指针
	u32 m_uSize;

	PMsgTypeBinary()
		: m_uSize(0)
		, m_uCrc32(0)
		, m_pData(NULL)
	{
	}
	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		u32 uExtra = sizeof(m_uCrc32) + sizeof(m_uSize);
		if (a_uLimit < uExtra + m_uSize)
		{
			return 0;
		}
		m_uCrc32 = GenerateCRC32C(m_pData, m_uSize);

		tcchar* pSize = (tcchar*)&m_uSize;
		tcchar* pCrc  = (tcchar*)&m_uCrc32;
#if T_ENDIAN == T_LITTLE_ENDIAN
		a_pData[0] = pSize[0];
		a_pData[1] = pSize[1];
		a_pData[2] = pSize[2];
		a_pData[3] = pSize[3];
		a_pData[4] = pCrc[0];
		a_pData[5] = pCrc[1];
		a_pData[6] = pCrc[2];
		a_pData[7] = pCrc[3];
#else
		a_pData[0] = pSize[3];
		a_pData[1] = pSize[2];
		a_pData[2] = pSize[1];
		a_pData[3] = pSize[0];
		a_pData[4] = pCrc[3];
		a_pData[5] = pCrc[2];
		a_pData[6] = pCrc[1];
		a_pData[7] = pCrc[0];
#endif
		TMemcpy(a_pData + uExtra, a_uLimit - uExtra, m_pData, m_uSize);
		return uExtra + m_uSize;
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		u32 uExtra = sizeof(m_uCrc32) + sizeof(m_uSize);
		if (a_uLimit > BINARY_TYPE_LENGTH + uExtra)
		{
			return 0;
		}
		tcchar* pSize = (tcchar*)&m_uSize;
		tcchar* pCrc  = (tcchar*)&m_uCrc32;
#if T_ENDIAN == T_LITTLE_ENDIAN
		pSize[0] = a_pData[0];
		pSize[1] = a_pData[1];
		pSize[2] = a_pData[2];
		pSize[3] = a_pData[3];
		pCrc[0] = a_pData[4];
		pCrc[1] = a_pData[5];
		pCrc[2] = a_pData[6];
		pCrc[3] = a_pData[7];
#else
		pSize[0] = a_pData[3];
		pSize[1] = a_pData[2];
		pSize[2] = a_pData[1];
		pSize[3] = a_pData[0];
		pCrc[0] = a_pData[7];
		pCrc[1] = a_pData[6];
		pCrc[2] = a_pData[5];
		pCrc[3] = a_pData[4];
#endif
		m_pData = a_pData + uExtra;
		u32 uCrC = GenerateCRC32C(m_pData, m_uSize);
// 		if (uCrC != m_uCrc32)
// 		{
// 			return 0;
// 		}

		return m_uSize + uExtra;
	}

	T_INLINE u32 GetLength() const
	{
		return m_uSize + sizeof(m_uCrc32) + sizeof(m_uSize);
	}
};

typedef PMsgTypeBinary PMsgTypeSTR;
typedef PMsgTypeBinary PMsgTypeLOB;


#pragma pack(push, 1)

struct MessageHeader
{
	PMsgTypeU32 m_uMsgID;
	PMsgTypeU32 m_uLength;
	PMsgTypeN8 m_nCompress;
	MessageHeader()
	{
		TMemzero(this, sizeof(MessageHeader));
	}
	T_INLINE u32 Serialize(tcchar* a_pData, u32 a_uLimit) const
	{
		u32 uTotalLength = m_uMsgID.GetLength() + m_uLength.GetLength() + m_nCompress.GetLength();
		if (uTotalLength > a_uLimit)
		{
			return 0;
		}
		u32 uOffset = 0;

		m_uMsgID.Serialize(a_pData + uOffset, a_uLimit - uOffset);
		uOffset += m_uMsgID.GetLength();

		m_uLength.Serialize(a_pData + uOffset, a_uLimit - uOffset);
		uOffset += m_uLength.GetLength();

		m_nCompress.Serialize(a_pData + uOffset, a_uLimit - uOffset);
		uOffset += m_nCompress.GetLength();
		 
		return uOffset;
	}
	T_INLINE u32 Deserialize(const tcchar* a_pData, u32 a_uLimit)
	{
		u32 uOffset = 0;

		m_uMsgID.Deserialize(a_pData + uOffset, a_uLimit - uOffset);
		uOffset += m_uMsgID.GetLength();

		m_uLength.Deserialize(a_pData + uOffset, a_uLimit - uOffset);
		uOffset += m_uLength.GetLength();

		m_nCompress.Deserialize(a_pData + uOffset, a_uLimit - uOffset);
		uOffset += m_nCompress.GetLength();

		return uOffset;
	}
	T_INLINE u32 GetLength() const
	{
		return m_uMsgID.GetLength() + m_uLength.GetLength() + m_nCompress.GetLength();
	}

	T_INLINE u32 GetMsgID() const
	{
		return m_uMsgID.m_value;
	}

	T_INLINE void SetMsgID(u32 a_uMsgID)
	{
		m_uMsgID.m_value = a_uMsgID;
	}

	T_INLINE u32 GetMsgLength() const
	{
		return m_uLength.m_value;
	}

	T_INLINE void SetMsgLength(u32 a_uMsgLength)
	{
		m_uLength.m_value = a_uMsgLength;
	}

	T_INLINE n8 GetCompress() const
	{
		return m_nCompress.m_value;
	}

	T_INLINE void SetCompress(n8 a_nCompress)
	{
		m_nCompress.m_value = a_nCompress;
	}
};

#pragma pack(pop)



