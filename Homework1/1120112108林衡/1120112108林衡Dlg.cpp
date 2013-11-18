
// 1120112108林衡Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1120112108林衡.h"
#include "1120112108林衡Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy1120112108林衡Dlg 对话框




CMy1120112108林衡Dlg::CMy1120112108林衡Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1120112108林衡Dlg::IDD, pParent)
	, m_streditRXDATADISP(_T(""))
	, m_streditTXDATAINPUT(_T(""))
	, m_bSerialPortOpened(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bSerialPortOpened = false;
}

void CMy1120112108林衡Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RXDATADISP, m_streditRXDATADISP);
	DDX_Text(pDX, IDC_EDIT_TXDATAINPUT, m_streditTXDATAINPUT);
	DDX_Control(pDX, IDC_COMBO_PORTNO, m_ctrlcomboPORTNO);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ctrlcomboBAUDRATE);
	DDX_Control(pDX, IDC_COMBO_BYTESIZES, m_ctrlcomboBYTESIZES);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_ctrlcomboSTOPBITS);
}

BEGIN_MESSAGE_MAP(CMy1120112108林衡Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_PORTNO, &CMy1120112108林衡Dlg::OnCbnSelchangeComboPortno)
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT, &CMy1120112108林衡Dlg::OnBnClickedButtonOpenport)
	ON_BN_CLICKED(IDC_BUTTON_SENDDATA, &CMy1120112108林衡Dlg::OnBnClickedButtonSenddata)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEPORT, &CMy1120112108林衡Dlg::OnBnClickedButtonCloseport)
	ON_MESSAGE(ON_COM_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY_SENDBOX, &CMy1120112108林衡Dlg::OnBnClickedButtonEmptySendbox)
	ON_BN_CLICKED(IDC_BUTTON_EMPTYREXBOX, &CMy1120112108林衡Dlg::OnBnClickedButtonEmptyrexbox)
END_MESSAGE_MAP()


// CMy1120112108林衡Dlg 消息处理程序

BOOL CMy1120112108林衡Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
	m_ctrlcomboPORTNO.SetCurSel(0);
	m_ctrlcomboBAUDRATE.SetCurSel(1);
	m_ctrlcomboBYTESIZES.SetCurSel(2);
	m_ctrlcomboSTOPBITS.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy1120112108林衡Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1120112108林衡Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy1120112108林衡Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy1120112108林衡Dlg::OnCbnSelchangeComboPortno()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMy1120112108林衡Dlg::OnBnClickedButtonOpenport()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPortNo = m_ctrlcomboPORTNO.GetCurSel()+1;
	int arrayBAUDRATE[] = {19200,9600};
	BYTE arrayBYTESIZES[] = {6,7,8};
	BYTE arraySTOPBITS[] = {0,2};
	int nBaudRate = arrayBAUDRATE[m_ctrlcomboBAUDRATE.GetCurSel()];
	BYTE nByteSizes = arrayBYTESIZES[m_ctrlcomboBYTESIZES.GetCurSel()];
	BYTE nStopBits = arraySTOPBITS[m_ctrlcomboSTOPBITS.GetCurSel()];
	m_CnComm.Open(nPortNo, nBaudRate, NOPARITY , nByteSizes,nStopBits);
	//m_CnComm.Open(nPortNo);
	if(m_CnComm.IsOpen())
	{
		AfxMessageBox(_T("串口已经成功打开"));
		m_CnComm.SetWnd(this->m_hWnd);
		m_bSerialPortOpened=TRUE;
	}
	else
	{
		AfxMessageBox(_T("串口打开失败"));
		m_bSerialPortOpened=false;
	}
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);

}


void CMy1120112108林衡Dlg::OnBnClickedButtonSenddata()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bSerialPortOpened)
	{
		AfxMessageBox(_T("请先打开串口"));
		return;
	}
	UpdateData(TRUE);
	//AfxMessageBox(m_strEditTXDataInput);
	CStringA straTemp;
    straTemp = m_streditTXDATAINPUT; //UniCode字符串与ANSI字符串之间的转换
	m_CnComm.Write(straTemp);
	//m_CnComm.Write(m_streditTXDATAINPUT);
	UpdateData(FALSE);

}


void CMy1120112108林衡Dlg::OnBnClickedButtonCloseport()
{
	m_CnComm.Close();
	m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);

	// TODO: 在此添加控件通知处理程序代码
}

LRESULT CMy1120112108林衡Dlg::OnReceive(WPARAM port, LPARAM ch)
{
	char str[100];
	m_CnComm.ReadString(str, 100);
	/*for(int i =0;i < strlen(str);i++) 
		
	{
		str[i]= str[i];
		m_streditRXDATADISP += str[i];
	}*/
	m_streditRXDATADISP += str;
	UpdateData(false);
	return 0;
}



void CMy1120112108林衡Dlg::OnBnClickedButtonEmptySendbox()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_TXDATAINPUT,_T(""));
	m_streditTXDATAINPUT.Empty();
	UpdateData(false);
	
}


void CMy1120112108林衡Dlg::OnBnClickedButtonEmptyrexbox()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_RXDATADISP,_T(""));
	m_streditRXDATADISP.Empty();
	UpdateData(false);
}
