
// PropertyGridDlg.h : ��� ����
//

#pragma once
#include "afxpropertygridctrl.h"
#include "gParameter.h"

// CPropertyGridDlg ��ȭ ����
class CPropertyGridDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPropertyGridDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	void CPropertyGridDlg::InitProperty();
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
	void CPropertyGridDlg::CreateParam();
	void CPropertyGridDlg::SyncParamToProperty();
	void CPropertyGridDlg::SyncPropertyToParam();

	gParameter _param;
	CMFCPropertyGridCtrl m_property;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedBtnSave2();
};
