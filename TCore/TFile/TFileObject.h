//�����ļ�����
#pragma once

namespace TCore
{
	namespace TFile
	{
		class T_DLL_EXPORT CFileObject
		{
		private:
			FILE* m_pFile;
			tbool m_bCanRead;
			tbool m_bCanWrite;
		public:
			CFileObject()
				: m_pFile(NULL)
				, m_bCanRead(false)
				, m_bCanWrite(false)
			{}
			~CFileObject() {}
			//���ļ�
			tbool open(const tcchar* a_pFileName, EFileMode a_eMode);

			//�õ���ǰ�ļ�ָ��λ��
			n32 getPosition();

			//���õ�ǰ�ļ�ָ���λ��
			n32 seek(n32 a_nOffset, ESeekOrigin a_eSeekOrigin);

			//��ȡ�޶����ȵ�����
			tbool readBuffer(tcchar* a_oBuffer, n32 a_nLen);

			//��ȡ�ļ�һ��
			tcchar* readLine(tcchar* a_oBuffer, n32 a_nLen);

			//��ȡһ���ַ�
			tcchar readChar();

			//д���޶����ȵ�����
			tbool writeBuffer(const tcchar* a_oBuffer, n32 a_nLen);

			//д��һ������
			tbool writeLine(const tcchar* a_buffer);

			//дһ���ַ�
			tbool writeChar(tcchar a_buffer);

			//�õ��ļ��ܳ���
			n32 getFileSize();

			//��������������д���ļ�
			void flush();

			tbool canRead()
			{
				return (m_pFile != NULL && m_bCanRead == true);
			}

			tbool canWrite()
			{
				return (m_pFile != NULL && m_bCanWrite == true);
			}

			//�ر��ļ�
			void close();

			//////////////////////////////////////////////////////////////////////////
		};
	}
}

