
// PropertyGrid.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPropertyGridApp:
// �� Ŭ������ ������ ���ؼ��� PropertyGrid.cpp�� �����Ͻʽÿ�.
//

class CPropertyGridApp : public CWinApp
{
public:
	CPropertyGridApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPropertyGridApp theApp;