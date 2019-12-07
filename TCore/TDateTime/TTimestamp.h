#pragma once 

namespace TCore
{
	namespace TTime
	{
		class T_DLL_API TTimestamp
		{
		private:
			time_t m_t;
		public:
			//�õ�ǰʱ�乹��һ��ʱ���
			TTimestamp()
			{
				Update();
			}

			T_INLINE void Update()
			{
				m_t = time(NULL);
				m_t = m_t + TIME_ZONE_SPANS;
			}

			T_INLINE u32 GetStamp()
			{
				return (u32)m_t;
			}

			T_INLINE time_t GetSTime()
			{
				return m_t;
			}

			~TTimestamp(){}
		};
	}
}


