
// 1120112108linheng_Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C1120112108linheng_ServerApp:
// �йش����ʵ�֣������ 1120112108linheng_Server.cpp
//

class C1120112108linheng_ServerApp : public CWinApp
{
public:
	C1120112108linheng_ServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C1120112108linheng_ServerApp theApp;