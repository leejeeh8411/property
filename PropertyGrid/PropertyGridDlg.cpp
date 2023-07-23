
// PropertyGridDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PropertyGrid.h"
#include "PropertyGridDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPropertyGridDlg 대화 상자



CPropertyGridDlg::CPropertyGridDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROPERTYGRID_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPropertyGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID1, m_property);
}

BEGIN_MESSAGE_MAP(CPropertyGridDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPropertyGridDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CPropertyGridDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPropertyGridDlg 메시지 처리기

BOOL CPropertyGridDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	Init();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPropertyGridDlg::Init()
{
	HDITEM item;
	item.cxy = 150;
	item.mask = HDI_WIDTH;
	m_property.GetHeaderCtrl().SetItem(0, &HDITEM(item));

	CMFCPropertyGridProperty* pGroupInput = new CMFCPropertyGridProperty("Input");
	m_property.AddProperty(pGroupInput);

	CMFCPropertyGridProperty* pGroupInput_data1 = new CMFCPropertyGridProperty("Sel Data", "None", "Select object");
	pGroupInput_data1->AddOption("NO Sel");
	pGroupInput_data1->AddOption("Option1");
	pGroupInput_data1->AddOption("Option2");
	pGroupInput_data1->AddOption("Option3");
	pGroupInput_data1->AllowEdit(FALSE);
	pGroupInput->AddSubItem(pGroupInput_data1);

	CMFCPropertyGridProperty* pGroupInput2 = new CMFCPropertyGridProperty("Input2");
	m_property.AddProperty(pGroupInput2);

	bool bData = false;
	int nData = 30;
	double dData = 3.4;
	CString strData = "strData123";

	CMFCPropertyGridProperty* pGroupInput_data2 = new CMFCPropertyGridProperty("Bool Data", (_variant_t)bData, "Select object");
	CMFCPropertyGridProperty* pGroupInput_data3 = new CMFCPropertyGridProperty("int Data", (_variant_t)nData, "Select object");
	CMFCPropertyGridProperty* pGroupInput_data4 = new CMFCPropertyGridProperty("double Data", (_variant_t)dData, "Select object");
	CMFCPropertyGridProperty* pGroupInput_data5 = new CMFCPropertyGridProperty("string Data", (_variant_t)strData, "Select object");
	//pGroupInput_data2->AllowEdit(FALSE);
	pGroupInput2->AddSubItem(pGroupInput_data2);
	pGroupInput2->AddSubItem(pGroupInput_data3);
	pGroupInput2->AddSubItem(pGroupInput_data4);
	pGroupInput2->AddSubItem(pGroupInput_data5);

}
void CPropertyGridDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPropertyGridDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPropertyGridDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPropertyGridDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CPropertyGridDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMFCPropertyGridProperty* getGroup1 = m_property.GetProperty(1);
	CMFCPropertyGridProperty* getSub1 = getGroup1->GetSubItem(0);
	CMFCPropertyGridProperty* getSub2 = getGroup1->GetSubItem(1);
	CMFCPropertyGridProperty* getSub3 = getGroup1->GetSubItem(2);
	CMFCPropertyGridProperty* getSub4 = getGroup1->GetSubItem(3);

	COleVariant vars_bool = getSub1->GetValue();
	COleVariant vars_int = getSub2->GetValue();
	COleVariant vars_double = getSub3->GetValue();
	COleVariant vars_string = getSub4->GetValue();

	//변환
	bool bData = vars_bool.boolVal;
	int nData = vars_int.iVal;
	double dData = vars_double.dblVal;
	CString str = (LPCTSTR)(_bstr_t)vars_string.bstrVal;

	
	// first, create a file instance
	mINI::INIFile file("D:\\myfile.ini");

	// next, create a structure that will hold data
	mINI::INIStructure ini;

	// now we can read the file
	file.read(ini);

	std::string strSection = "fruits";
	std::string strDataName = "apples";
	// read a value
	std::string& amountOfApples = ini[strSection][strDataName];

	// update a value
	ini[strSection]["oranges"] = "20";

	// add a new entry
	ini[strSection]["bananas"] = "3.4";

	// write updates to file
	file.write(ini);
}
