
// 1120112108LinHeng.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// 1120112108LinHengApp:
// �йش����ʵ�֣������ 1120112108LinHeng.cpp
//

class CMy1120112108LinHengApp : public CWinApp
{
public:
	CMy1120112108LinHengApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy1120112108LinHengApp theApp;