
// MFCEx02.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCEx02App:
// �� Ŭ������ ������ ���ؼ��� MFCEx02.cpp�� �����Ͻʽÿ�.
//

class CMFCEx02App : public CWinApp
{
public:
	CMFCEx02App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCEx02App theApp;