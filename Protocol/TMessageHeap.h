#pragma once

class TMessageHeapInterface
{
public :
	TMessageHeapInterface(){}
	virtual ~TMessageHeapInterface(){}
	virtual tcchar* Require(u32 a_uSize) T_PURE;
};

class TMessageHeapContainer
{
	TMessageHeapInterface* m_pHeap;
public:
	TMessageHeapContainer() : m_pHeap(NULL)
	{
	}

	void RegisterHeap(TMessageHeapInterface* a_pHeap)
	{
		m_pHeap = a_pHeap;
	}
	void UnRegisterHeap(TMessageHeapInterface* a_pHeap)
	{
		if (a_pHeap == m_pHeap)
		{
			m_pHeap = NULL;
		}
	}
	TMessageHeapInterface* GetInstance()
	{
		if (m_pHeap == NULL)
		{
			return NULL;
		}
		return m_pHeap;
	}
	tcchar* Require(u32 a_uSize)
	{
		if (m_pHeap == NULL)
		{
			return NULL;
		}
		return m_pHeap->Require(a_uSize);
	}

	static TMessageHeapContainer& Instance()
	{
		static TMessageHeapContainer rContainer;
		return rContainer;
	}
};


class TMessageSendHeap : public TMessageHeapInterface
{
private:
	u32 m_uCapablity;		//����ݻ�
	tcchar* m_pCurrent;		//��ǰλ��
	tcchar* m_pHeap;		//��ʼ��ַ

public:
	TMessageSendHeap()
		: m_uCapablity(0)
		, m_pCurrent(NULL)
		, m_pHeap(NULL)
	{

	}

	void AllocHeap(u32 a_uSize)
	{
		m_pHeap = new tcchar[a_uSize];
		m_uCapablity = a_uSize;
		m_pCurrent = m_pHeap;
	}

	u32 GetCapablity() const
	{
		return m_uCapablity;
	}

	//Ĭ�Ͽռ��㹻�������ڻ��λ������ĸ���
	virtual tcchar* Require(u32 a_uSize)
	{
		a_uSize = ((a_uSize + 3) / 4) * 4;
		//���ʣ�µĿռ䲻������ͷ����
		if (m_pCurrent - m_pHeap + a_uSize > m_uCapablity)
		{
			m_pCurrent = m_pHeap;
		}
		tcchar* pResult = m_pCurrent;
		m_pCurrent += a_uSize;
		return pResult;
	}
	
	void clear()
	{
		if(m_pHeap != NULL)
		{
			delete m_pHeap;
			m_pHeap = NULL;
		}
	}

	virtual ~TMessageSendHeap()
	{
		clear();
	}
};


T_INLINE void RegisterMessageHeap(TMessageHeapInterface* a_pHeap)
{
	TMessageHeapContainer::Instance().RegisterHeap(a_pHeap);
}

T_INLINE void UnRegisterMessageHeap(TMessageHeapInterface* a_pHeap)
{
	TMessageHeapContainer::Instance().UnRegisterHeap(a_pHeap);
}
T_INLINE tcchar* RequireMessageHeap(u32 a_uSize)
{
	return TMessageHeapContainer::Instance().Require(a_uSize);
}

