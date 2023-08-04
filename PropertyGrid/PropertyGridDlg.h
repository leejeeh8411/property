
// PropertyGridDlg.h : 헤더 파일
//

#pragma once
#include "afxpropertygridctrl.h"
#include "gParameter.h"

// CPropertyGridDlg 대화 상자
class CPropertyGridDlg : public CDialogEx
{
// 생성입니다.
public:
	CPropertyGridDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	void CPropertyGridDlg::InitProperty();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPERTYGRID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
