
// MFCEx01.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCEx01App:
// �� Ŭ������ ������ ���ؼ��� MFCEx01.cpp�� �����Ͻʽÿ�.
//

class CMFCEx01App : public CWinApp
{
public:
	CMFCEx01App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCEx01App theApp;