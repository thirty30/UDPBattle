#pragma once

#ifndef _WIN32_WINNT            // ָ��Ҫ������ƽ̨��Windows7
#define _WIN32_WINNT 0x0601     // ����ֵ����Ϊ��Ӧ��ֵ��������Windows�������汾��
#endif

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <math.h>
#include <stdarg.h>		//����ʡ�Բ���va_list va_start�ȵ�ͷ�ļ�
#include <time.h>
using namespace std;

#include <windows.h>
#include <io.h>
#include <share.h>

/////////////////////////ʹ��stlport����Ľṹ////////////////////////
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <hash_set>
//#include <unordered_set>
//#include <unordered_map>

//////////////////////////////////////////////////////////////////////////
