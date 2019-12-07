#pragma once

#define TFileOpen _fsopen
#define TFileClose fclose


//��ģʽ��b��û��b������
//windows�£�
//��b:�����Ƶķ�ʽ���ֽڶ������������������/r/n��ô�����/r/n ��2���ֽ�
//û��b���ı���ʽ�����������������/r/n ������ֻ��/n ��1���ֽ�
//linux�£�
//��β��\r\n����û��b�ķ�ʽ������������ַ���������û������

enum EFileMode
{
	E_FILE_CREATE_NEW	= 1,		//wb
	E_FILE_READ			= 2,		//r		�ı��� ��������
	E_FILE_WRITE		= 3,		//w		�ı�д ��������
	E_FILE_APPEND		= 4,		//a		�ı�׷�� ��������
	E_FILE_B_READ		= 5,		//rb
	E_FILE_B_WRITE		= 6,		//wb
	E_FILE_B_APPEND		= 7,		//ab
};

enum ESeekOrigin
{
	E_FILE_SEEK_BEGIN	= SEEK_SET,
	E_FILE_SEEK_CURRENT	= SEEK_CUR,
	E_FILE_SEEK_END		= SEEK_END,
};

#include "./TFileObject.h"
#include "./TFileConfig.h"

using namespace TCore::TFile;


