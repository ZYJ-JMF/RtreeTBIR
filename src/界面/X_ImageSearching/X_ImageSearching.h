
// X_ImageSearching.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CX_ImageSearchingApp:
// �йش����ʵ�֣������ X_ImageSearching.cpp
//

class CX_ImageSearchingApp : public CWinApp
{
public:
	CX_ImageSearchingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CX_ImageSearchingApp theApp;