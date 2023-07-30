
// PropertyGridDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PropertyGrid.h"
#include "PropertyGridDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CPropertyGridDlg ��ȭ ����



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


// CPropertyGridDlg �޽��� ó����

BOOL CPropertyGridDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CreateParam();
	Init();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//�Ķ���� ���¸� �ʱ�ȭ �Ѵ�.
void CPropertyGridDlg::CreateParam()
{
	//�Ķ���� ��� ����
	_param.SetParameterPath("D:\\para.ini");

	//�׷� ����
	CString strGroup[2];
	strGroup[0].Format("Input");
	strGroup[1].Format("Output");

	//�Ķ���� �ʱ�ȭ
	//�ϴ� �� �۾��� ���α׷� ������ ����� ini ���� �� �ε尡 ������
	bool inb = true;
	pair<string, PARAM> makedParamIn1 = _param.MakeParam(strGroup[0], "input_bool", inb);
	_param.SetParam(makedParamIn1);
	int inn = 34;
	pair<string, PARAM> makedParamIn2 = _param.MakeParam(strGroup[0], "input_int", inn);
	_param.SetParam(makedParamIn2);
	float inf = 2.4;
	pair<string, PARAM> makedParamIn3 = _param.MakeParam(strGroup[0], "input_float", inf);
	_param.SetParam(makedParamIn3);
	double ind = 3.56;
	pair<string, PARAM> makedParamIn4 = _param.MakeParam(strGroup[0], "input_double", ind);
	_param.SetParam(makedParamIn4);
	CString instr = "abcdefg";
	pair<string, PARAM> makedParamIn5 = _param.MakeParam(strGroup[0], "input_string", instr);
	_param.SetParam(makedParamIn5);

	bool ob = true;
	pair<string, PARAM> makedParamOut1 = _param.MakeParam(strGroup[1], "output_bool", ob);
	_param.SetParam(makedParamOut1);
	int on = 34;
	pair<string, PARAM> makedParamOut2 = _param.MakeParam(strGroup[1], "output_int", on);
	_param.SetParam(makedParamOut2);
	float of = 2.4;
	pair<string, PARAM> makedParamOut3 = _param.MakeParam(strGroup[1], "output_float", of);
	_param.SetParam(makedParamOut3);
	double od = 3.56;
	pair<string, PARAM> makedParamOut4 = _param.MakeParam(strGroup[1], "output_double", od);
	_param.SetParam(makedParamOut4);
	CString ostr = "abcdefg";
	pair<string, PARAM> makedParamOut5 = _param.MakeParam(strGroup[1], "output_string", ostr);
	_param.SetParam(makedParamOut5);

	string param_path = _param.GetParameterPath();
	CFileFind fileFind;
	BOOL bExist = fileFind.FindFile(param_path.c_str());

	if (bExist == true) {
		_param.LoadParam();
	}

	_param.SaveParam();

}

void CPropertyGridDlg::Init()
{
	HDITEM item;
	item.cxy = 150;
	item.mask = HDI_WIDTH;
	m_property.GetHeaderCtrl().SetItem(0, &HDITEM(item));

	//�׷�
	vector<string> group_list = _param.GetListGroup();
	for (int i = 0; i < group_list.size(); i++) {
		string group_name = group_list[i];
		CMFCPropertyGridProperty* main_group = new CMFCPropertyGridProperty(group_name.c_str());
		m_property.AddProperty(main_group);

		
		//�׷��̸����� ���� ����Ʈ�� �����´�.
		vector<string> vt_param_in_group = _param.GetListParamFromGroupName(group_name);

		for each (string key in vt_param_in_group) {
			//�ϴ� �Ķ���� ��������
			pair<string, PARAM> param = _param.GetParam(key);

			PARAM stParam = param.second;

			CMFCPropertyGridProperty* sub_group = NULL;

			if (stParam.nDataType == TYPE_BOOLEAN) {
				auto val = stParam.bValue;
				sub_group = new CMFCPropertyGridProperty(key.c_str(), (_variant_t)val, "Select object");
			}
			else if (stParam.nDataType == TYPE_INT) {
				auto val = stParam.nValue;
				sub_group = new CMFCPropertyGridProperty(key.c_str(), (_variant_t)val, "Select object");
			}
			else if (stParam.nDataType == TYPE_DOUBLE) {
				auto val = stParam.dValue;
				sub_group = new CMFCPropertyGridProperty(key.c_str(), (_variant_t)val, "Select object");
			}
			else if (stParam.nDataType == TYPE_STRING) {
				string val = stParam.chValue;
				sub_group = new CMFCPropertyGridProperty(key.c_str(), (_variant_t)val, "Select object");
			}

			//������ Ÿ�Կ� �°� ����׷쿡 ����Ѵ�
			main_group->AddSubItem(sub_group);

		}
	}

	//CMFCPropertyGridProperty* pGroupInput = new CMFCPropertyGridProperty("Input");
	//m_property.AddProperty(pGroupInput);

	//CMFCPropertyGridProperty* pGroupInput_data1 = new CMFCPropertyGridProperty("Sel Data", "None", "Select object");
	//pGroupInput_data1->AddOption("NO Sel");
	//pGroupInput_data1->AddOption("Option1");
	//pGroupInput_data1->AddOption("Option2");
	//pGroupInput_data1->AddOption("Option3");
	//pGroupInput_data1->AllowEdit(FALSE);
	//pGroupInput->AddSubItem(pGroupInput_data1);

	//CMFCPropertyGridProperty* pGroupInput2 = new CMFCPropertyGridProperty("Input2");
	//m_property.AddProperty(pGroupInput2);

	//bool bData = false;
	//int nData = 30;
	//double dData = 3.4;
	//CString strData = "strData123";

	//CMFCPropertyGridProperty* pGroupInput_data2 = new CMFCPropertyGridProperty("Bool Data", (_variant_t)bData, "Select object");
	//CMFCPropertyGridProperty* pGroupInput_data3 = new CMFCPropertyGridProperty("int Data", (_variant_t)nData, "Select object");
	//CMFCPropertyGridProperty* pGroupInput_data4 = new CMFCPropertyGridProperty("double Data", (_variant_t)dData, "Select object");
	//CMFCPropertyGridProperty* pGroupInput_data5 = new CMFCPropertyGridProperty("string Data", (_variant_t)strData, "Select object");
	//pGroupInput2->AddSubItem(pGroupInput_data2);
	//pGroupInput2->AddSubItem(pGroupInput_data3);
	//pGroupInput2->AddSubItem(pGroupInput_data4);
	//pGroupInput2->AddSubItem(pGroupInput_data5);

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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPropertyGridDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CPropertyGridDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPropertyGridDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void CPropertyGridDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMFCPropertyGridProperty* getGroup1 = m_property.GetProperty(1);
	CMFCPropertyGridProperty* getSub1 = getGroup1->GetSubItem(0);
	CMFCPropertyGridProperty* getSub2 = getGroup1->GetSubItem(1);
	CMFCPropertyGridProperty* getSub3 = getGroup1->GetSubItem(2);
	CMFCPropertyGridProperty* getSub4 = getGroup1->GetSubItem(3);

	COleVariant vars_bool = getSub1->GetValue();
	COleVariant vars_int = getSub2->GetValue();
	COleVariant vars_double = getSub3->GetValue();
	COleVariant vars_string = getSub4->GetValue();

	//��ȯ
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
