#pragma once

class PMessageBase
{
public:
	virtual u32 GetLength() const T_PURE;
	virtual u32 Serialize(tcchar* a_pData, u32 a_uLimit) const  T_PURE;
	virtual u32 Deserialize(const tcchar* a_pData, u32 a_uLimit) T_PURE;
};



