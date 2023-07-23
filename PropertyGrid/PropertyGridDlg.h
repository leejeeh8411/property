
// PropertyGridDlg.h : ��� ����
//

#pragma once
#include "afxpropertygridctrl.h"
#include "ini.h"

// CPropertyGridDlg ��ȭ ����
class CPropertyGridDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPropertyGridDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	void CPropertyGridDlg::Init();
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPERTYGRID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCPropertyGridCtrl m_property;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
