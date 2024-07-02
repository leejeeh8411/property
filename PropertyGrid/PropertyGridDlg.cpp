
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
	ON_BN_CLICKED(IDC_BTN_SAVE2, &CPropertyGridDlg::OnBnClickedBtnSave2)
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
	InitProperty();
	SyncParamToProperty();


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//�Ķ���� ���¸� �ʱ�ȭ �Ѵ�.
void CPropertyGridDlg::CreateParam()
{
	//�Ķ���� ��� ����
	_param.SetParameterPath("D:\\para.ini");

	//�׷� ����
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

//���̾�α׻� ��� ������Ƽ�� paramŬ�������� ������ ������ ������Ʈ ���ش�.
void CPropertyGridDlg::SyncParamToProperty()
{
	//�׷�
	vector<string> group_list = _param.GetListGroup();
	for (int i = 0; i < group_list.size(); i++) {
		string group_name = group_list[i];
		CMFCPropertyGridProperty* main_group = new CMFCPropertyGridProperty((CString)group_name.c_str());
		m_property.AddProperty(main_group);


		//�׷��̸����� ���� ����Ʈ�� �����´�.
		vector<string> vt_param_in_group = _param.GetListParamFromGroupName(group_name);

		for each (string key in vt_param_in_group) {
			//�ϴ� �Ķ���� ��������
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

			//������ Ÿ�Կ� �°� ����׷쿡 ����Ѵ�
			main_group->AddSubItem(sub_group);

		}
	}
}

//���̾�α׻� ��� ������Ƽ�� ������ paramŬ������ ���� �� update�Ѵ�(with ini save).
void CPropertyGridDlg::SyncPropertyToParam()
{
	//gParameter���� �׷������� �����ͼ� �ش��ϴ� ������ Ÿ���� ������ ��,
	//�� �����Ϳ� �´� Ÿ������ �ٽ� gParameter�� set �Ѵ�.

	vector<string> group_list = _param.GetListGroup();
	for (int group_idx = 0; group_idx < group_list.size(); group_idx++) {
		string group_name = group_list[group_idx];

		//�׷��� �����´�
		CMFCPropertyGridProperty* get_group = m_property.GetProperty(group_idx);	

		//�׷��̸����� ���� ����Ʈ�� �����´�.
		vector<string> vt_param_in_group = _param.GetListParamFromGroupName(group_name);

		for (int sub_group_idx = 0; sub_group_idx < vt_param_in_group.size(); sub_group_idx++){
			
			string key = vt_param_in_group[sub_group_idx];
			
			//���� �׷� ��������
			CMFCPropertyGridProperty* get_sub_group = get_group->GetSubItem(sub_group_idx);

			//�ϴ� �Ķ���� ��������
			shared_ptr<pair<string, PARAM>> ptr_param;
			ptr_param = _param.GetParam(key);
						
			PARAM* pParam = &ptr_param->second;

			COleVariant vars = get_sub_group->GetValue();

			//�Ķ���Ϳ� �� ������ Ÿ���� �� ��, ��ȯ
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
	
}

void CPropertyGridDlg::OnBnClickedBtnSave2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SyncPropertyToParam();
}
