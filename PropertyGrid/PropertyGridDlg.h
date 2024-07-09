
// PropertyGridDlg.h : ��� ����
//

#pragma once
#include "afxpropertygridctrl.h"
#include "Parameter.h"

// CPropertyGridDlg ��ȭ ����
class CPropertyGridDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPropertyGridDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

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
	void InitProperty(CMFCPropertyGridCtrl* pPropertyGridCtrl);
	void AddParameter(Parameter* pParameter, string groupName, string key, PARAM param);
	void ParameterSyncToFile(Parameter* pParameter);
	void SyncCtrl_ParamToCtrl(CMFCPropertyGridCtrl* pPropertyGridCtrl, Parameter* pParameter);
	void SyncCrtl_CtrlToParam(CMFCPropertyGridCtrl* pPropertyGridCtrl, Parameter* pParameter);
	
	Parameter* m_pParameter;
	CMFCPropertyGridCtrl m_property;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnSave2();
};
