
// 1120112108linheng_ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1120112108linheng_Client.h"
#include "1120112108linheng_ClientDlg.h"
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


// C1120112108linheng_ClientDlg 对话框



C1120112108linheng_ClientDlg::C1120112108linheng_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C1120112108linheng_ClientDlg::IDD, pParent)
	, m_strEditIPAddr(_T(""))
	, m_unEditPortNO(0)
	, m_strEditSendData(_T(""))
	, m_strEditRecvData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strEditIPAddr = _T("127.0.0.1"); //127.0.0.1 是本机IP 地址，也可以填入本机的真实IP 地址
	m_unEditPortNO = 5050; //注意了：如果安装了病毒防火墙，要把相应端口打开
	m_strEditRecvData = _T("");
	m_strEditSendData = _T("");
	m_bLinked=FALSE;   //网络是否连接，初始状态置为断
}

void C1120112108linheng_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IPADDR, m_strEditIPAddr);
	DDX_Text(pDX, IDC_EDIT_PORTNO, m_unEditPortNO);
	DDX_Text(pDX, IDC_EDIT_SENDDATA, m_strEditSendData);
	DDX_Text(pDX, IDC_EDIT_RECVDATA, m_strEditRecvData);
}

BEGIN_MESSAGE_MAP(C1120112108linheng_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LINK, &C1120112108linheng_ClientDlg::OnBnClickedButtonLink)
	ON_BN_CLICKED(IDC_BUTTON_UNLINK, &C1120112108linheng_ClientDlg::OnBnClickedButtonUnlink)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &C1120112108linheng_ClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &C1120112108linheng_ClientDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// C1120112108linheng_ClientDlg 消息处理程序

BOOL C1120112108linheng_ClientDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C1120112108linheng_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C1120112108linheng_ClientDlg::OnPaint()
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
HCURSOR C1120112108linheng_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C1120112108linheng_ClientDlg::OnBnClickedButtonLink()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pMySocket=new MySocket;
	m_pMySocket->Create();
	m_bLinked=m_pMySocket->Connect(m_strEditIPAddr, m_unEditPortNO);
	if(!m_bLinked)
	{
		AfxMessageBox("连接服务器失败");
	}
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(!m_bLinked);
	GetDlgItem(IDC_BUTTON_UNLINK)->EnableWindow(m_bLinked);
}



void C1120112108linheng_ClientDlg::OnBnClickedButtonUnlink()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bLinked) return; //如果没有连接，就返回
	if(m_pMySocket->ShutDown(2))//关闭接收与发送
	{
		m_bLinked=FALSE;
		Sleep(50);
		m_pMySocket->Close();
		if(m_pMySocket) delete m_pMySocket;
	}
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(!m_bLinked);
	GetDlgItem(IDC_BUTTON_UNLINK)->EnableWindow(m_bLinked);
}


void C1120112108linheng_ClientDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bLinked)
	{
		AfxMessageBox("没有连接网络");
		return;
	}
	UpdateData(TRUE);
	CTime t = CTime::GetCurrentTime();
	int d=t.GetDay(); //获得几号
	int y=t.GetYear(); //获取年份
	int m=t.GetMonth(); //获取当前月份
	int h=t.GetHour(); //获取当前为几时
	int mm=t.GetMinute(); //获取分钟
	int s=t.GetSecond(); //获取秒
	CString ti;
	ti.Format("%d.%d.%d-%d:%d:%d",y,m,d,h,mm,s);
	//AfxMessageBox(ti);
	CString tmpStr = m_strEditSendData + "|" + ti;
	m_pMySocket->Send(tmpStr, tmpStr.GetLength(),0);

}

void C1120112108linheng_ClientDlg::UpdateRXData(void)
{
	m_strEditRecvData=m_strRXDataTemp;
	UpdateData(FALSE);
}


void C1120112108linheng_ClientDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strEditSendData = "";
	m_strEditRecvData = "";
	UpdateData(FALSE);
}
