//ϣ������(shell����) �����ڻ�������������Ч�ʽϸ�
#pragma once 

namespace TCore
{
	namespace TArithmetic
	{
		template<typename T>
		T_INLINE void TShellSort(T* a_array, n32 a_nLen)
		{
			n32 nLen = a_nLen;
			n32 nSpan = 0;
			for (nSpan = (nLen / 2); nSpan >= 1; nSpan /= 2)
			{
				for (n32 i = nSpan; i < nLen; i++)
				{
					n32 nTemp = a_array[i];
					n32 j = i - nSpan;
					while (j >= 0 && a_array[j] > nTemp)
					{
						a_array[j + nSpan] = a_array[j];
						j -= nSpan;
					}
					a_array[j + nSpan] = nTemp;
				}
			}
		}
	}
}

