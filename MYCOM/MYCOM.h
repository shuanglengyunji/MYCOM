
// MYCOM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMYCOMApp:
// �йش����ʵ�֣������ MYCOM.cpp
//

class CMYCOMApp : public CWinApp
{
public:
	CMYCOMApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMYCOMApp theApp;