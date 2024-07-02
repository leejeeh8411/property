
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
	ON_BN_CLICKED(IDC_BTN_SAVE2, &CPropertyGridDlg::OnBnClickedBtnSave2)
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
	CreateParam();
	InitProperty();
	SyncParamToProperty();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

//파라미터 형태를 초기화 한다.
void CPropertyGridDlg::CreateParam()
{
	//파라미터 경로 설정
	_param.SetParameterPath("D:\\para.ini");

	//그룹 설정
	string strGroupName[2];
	strGroupName[0] = "Group 1";
	strGroupName[1] = "Group 2";

	string key = "input_bool";
	_param.CreateParam<bool>(strGroupName[0], key, DataType::TYPE_BOOLEAN, true);
	
	key = "input_int";
	_param.CreateParam<int>(strGroupName[0], key, DataType::TYPE_INT, 34);

	key = "input_float";
	_param.CreateParam<float>(strGroupName[0], key, DataType::TYPE_DOUBLE, 2.4);

	key = "input_double";
	_param.CreateParam<double>(strGroupName[0], key, DataType::TYPE_DOUBLE, 3.56);
	
	key = "input_string";
	_param.CreateParam<string>(strGroupName[0], key, DataType::TYPE_STRING, (string)"abcdefg");


	key = "output_bool";
	_param.CreateParam<bool>(strGroupName[1], key, DataType::TYPE_BOOLEAN, true);
	
	key = "output_int";
	_param.CreateParam<int>(strGroupName[1], key, DataType::TYPE_INT, 45);
	
	key = "output_float";
	_param.CreateParam<float>(strGroupName[1], key, DataType::TYPE_DOUBLE, 2.4);
	
	key = "output_double";
	_param.CreateParam<double>(strGroupName[1], key, DataType::TYPE_DOUBLE, 3.56);
	
	key = "output_string";
	_param.CreateParam<string>(strGroupName[1], key, DataType::TYPE_STRING, (string)"abcdefg");
	

	string param_path = _param.GetParameterPath();
	CFileFind fileFind;
	BOOL bExist = fileFind.FindFile((CString)param_path.c_str());

	if (bExist == true) {
		_param.LoadParam();
	}

	_param.SaveParam();

}

void CPropertyGridDlg::InitProperty()
{
	HDITEM item;
	item.cxy = 150;
	item.mask = HDI_WIDTH;
	m_property.GetHeaderCtrl().SetItem(0, &HDITEM(item));
}

//다이얼로그상에 모든 프로퍼티를 param클래스에서 정보를 가져와 업데이트 해준다.
void CPropertyGridDlg::SyncParamToProperty()
{
	//그룹
	vector<string> group_list = _param.GetListGroup();
	for (int i = 0; i < group_list.size(); i++) {
		string group_name = group_list[i];
		CMFCPropertyGridProperty* main_group = new CMFCPropertyGridProperty((CString)group_name.c_str());
		m_property.AddProperty(main_group);


		//그룹이름으로 하위 리스트를 가져온다.
		vector<string> vt_param_in_group = _param.GetListParamFromGroupName(group_name);

		for each (string key in vt_param_in_group) {
			//일단 파라미터 가져오자
			shared_ptr<pair<string, PARAM>> ptr_param;
			ptr_param = _param.GetParam(key);

			PARAM stParam = ptr_param->second;

			CMFCPropertyGridProperty* sub_group = NULL;

			if (stParam.nDataType == TYPE_BOOLEAN) {
				auto val = stParam.bValue;
				sub_group = new CMFCPropertyGridProperty((CString)key.c_str(), (_variant_t)val, TEXT("Select object"));
			}
			else if (stParam.nDataType == TYPE_INT) {
				auto val = stParam.nValue;
				sub_group = new CMFCPropertyGridProperty((CString)key.c_str(), (_variant_t)val, TEXT("Select object"));
			}
			else if (stParam.nDataType == TYPE_DOUBLE) {
				auto val = stParam.dValue;
				sub_group = new CMFCPropertyGridProperty((CString)key.c_str(), (_variant_t)val, TEXT("Select object"));
			}
			else if (stParam.nDataType == TYPE_STRING) {
				CString val = (CString)stParam.strValue.c_str();
				sub_group = new CMFCPropertyGridProperty((CString)key.c_str(), (_variant_t)val, TEXT("Select object"));
			}

			//데이터 타입에 맞게 서브그룹에 등록한다
			main_group->AddSubItem(sub_group);

		}
	}
}

//다이얼로그상에 모든 프로퍼티에 정보를 param클래스로 보낸 뒤 update한다(with ini save).
void CPropertyGridDlg::SyncPropertyToParam()
{
	//gParameter에서 그룹정보를 가져와서 해당하는 데이터 타입을 가져온 뒤,
	//그 데이터에 맞는 타입으로 다시 gParameter에 set 한다.

	vector<string> group_list = _param.GetListGroup();
	for (int group_idx = 0; group_idx < group_list.size(); group_idx++) {
		string group_name = group_list[group_idx];

		//그룹을 가져온다
		CMFCPropertyGridProperty* get_group = m_property.GetProperty(group_idx);	

		//그룹이름으로 하위 리스트를 가져온다.
		vector<string> vt_param_in_group = _param.GetListParamFromGroupName(group_name);

		for (int sub_group_idx = 0; sub_group_idx < vt_param_in_group.size(); sub_group_idx++){
			
			string key = vt_param_in_group[sub_group_idx];
			
			//하위 그룹 가져오기
			CMFCPropertyGridProperty* get_sub_group = get_group->GetSubItem(sub_group_idx);

			//일단 파라미터 가져오자
			shared_ptr<pair<string, PARAM>> ptr_param;
			ptr_param = _param.GetParam(key);
						
			PARAM* pParam = &ptr_param->second;

			COleVariant vars = get_sub_group->GetValue();

			//파라미터에 원 데이터 타입을 본 뒤, 변환
			if (pParam->nDataType == TYPE_BOOLEAN) {
				bool bData = vars.boolVal;
				pParam->bValue = bData;
			}
			else if (pParam->nDataType == TYPE_INT) {
				int nData = vars.iVal;
				pParam->nValue = nData;
			}
			else if (pParam->nDataType == TYPE_DOUBLE) {
				double dData = vars.dblVal;
				pParam->dValue = dData;
			}
			else if (pParam->nDataType == TYPE_STRING) {
				CString str = (LPCTSTR)(_bstr_t)vars.bstrVal;
				pParam->strValue = CT2CA(str);
			}

			_param.SetParam(ptr_param);
		}
	}

	_param.SaveParam();
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
	
}

void CPropertyGridDlg::OnBnClickedBtnSave2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SyncPropertyToParam();
}
