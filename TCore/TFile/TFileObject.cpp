#include "stdafx.h"

tbool CFileObject::open( const tcchar* a_pFileName, EFileMode a_eMode )
{
	if (m_pFile != NULL)
	{
		return false;
	}

	tcchar sMode[4] = {0};
	switch (a_eMode)
	{
	case E_FILE_CREATE_NEW:
		{
			sMode[0] = 'w';
			sMode[1] = 'b';
			m_bCanRead = true;
			m_bCanWrite = true;
		}
		break;
	case E_FILE_READ:
		{
			sMode[0] = 'r';
			m_bCanRead = true;
		}
		break;
	case E_FILE_WRITE:
		{
			sMode[0] = 'w';
			m_bCanWrite = true;
		}
		break;
	case E_FILE_APPEND:
		{
			sMode[0] = 'a';
			m_bCanWrite = true;
		}
		break;
	case E_FILE_B_READ:
		{
			sMode[0] = 'r';
			sMode[1] = 'b';
			m_bCanRead = true;
		}
		break;
	case E_FILE_B_WRITE:
		{
			sMode[0] = 'w';
			sMode[1] = 'b';
			m_bCanWrite = true;
		}
		break;
	case E_FILE_B_APPEND:
		{
			sMode[0] = 'a';
			sMode[1] = 'b';
			m_bCanWrite = true;
		}
		break;
	default:
		return false;
	}
	
	m_pFile = TFileOpen(a_pFileName, sMode, _SH_DENYWR);	//_SH_DENYWR���ֵ��ָ���ļ�ʱ��Ĺ���ʽ�����Ǵ�����ļ�ʱ���������̵Ķ�дȨ�� _SH_DENYWR�ǽ�ֹд

	if (m_pFile == NULL)
	{
		return false;
	}
	return true;
}

void CFileObject::close()
{
	if (m_pFile != NULL)
	{
		TFileClose(m_pFile);
	}
}

n32 CFileObject::getFileSize()
{
	if (m_pFile == NULL)
	{
		return 0;
	}
	//long ftell(FILE *stream)
	//ftell�ǵõ����ڵ��ļ�ָ��λ��

	//int fseek(FILE *stream, long offset, int fromwhere)
	//��fromwhereΪ��׼��ƫ��offset
	n32 oldPos = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_END);
	n32 length = ftell(m_pFile);
	fseek(m_pFile, oldPos, SEEK_SET);
	return length;
}

n32 CFileObject::getPosition()
{
	if (m_pFile == NULL)
	{
		return 0;
	}
	return ftell(m_pFile);
}

n32 CFileObject::seek(n32 a_nOffset, ESeekOrigin a_eSeekOrigin)
{
	return fseek(m_pFile, a_nOffset, a_eSeekOrigin);
}

tbool CFileObject::readBuffer( tcchar* a_oBuffer, n32 a_nLen )
{
	if (canRead() == false)
	{
		return false;
	}
	if (fread(a_oBuffer, a_nLen, 1, m_pFile) != 1)	//fread�ڶ������ļ��������������������ؿ���С�ڵ�3������
	{
		if (ferror(m_pFile) != 0)	//Ϊ�淵�ط�0  Ϊ�ٷ���0
		{
			return false;
		}
	}
	return true;
}

tcchar* CFileObject::readLine( tcchar* a_oBuffer, n32 a_nLen )
{
	if (canRead() == false)
	{
		return NULL;
	}

	return fgets(a_oBuffer, a_nLen, m_pFile);		//fgetsֱ�Ӷ���null('\0')����
}

tcchar CFileObject::readChar()
{
	if (canRead() == false)
	{
		return EOF;
	}

	return getc(m_pFile);
}

tbool CFileObject::writeBuffer(const tcchar* a_oBuffer, n32 a_nLen)
{
	if (canWrite() == false)
	{
		return false;
	}
	if (fwrite(a_oBuffer, a_nLen, 1, m_pFile) != 1)
	{
		return false;
	}
	return true;
}

tbool CFileObject::writeLine( const tcchar* a_buffer )
{
	if (canWrite() == false)
	{
		return false;
	}
	if (fputs(a_buffer, m_pFile) == EOF)
	{
		return false;
	}
	return true;
}

tbool CFileObject::writeChar( tcchar a_buffer )
{
	if (canWrite() == false)
	{
		return false;
	}
	if (putc(a_buffer, m_pFile) == EOF)
	{
		return false;
	}
	return true;
}

void CFileObject::flush()
{
	if (m_pFile == NULL)
	{
		return;
	}
	fflush(m_pFile);
}
