
// 1120112108linheng_ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1120112108linheng_Server.h"
#include "1120112108linheng_ServerDlg.h"
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


// C1120112108linheng_ServerDlg 对话框



C1120112108linheng_ServerDlg::C1120112108linheng_ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C1120112108linheng_ServerDlg::IDD, pParent)
	, m_strEditNetMsg(_T(""))
	, m_strEditComMsg(_T(""))
	, m_unEditPortNO(0)
{
	//{{AFX_DATA_INIT(CSServerDlg)
	m_unEditPortNO = 5050;
	m_strEditNetMsg = _T("");
	m_strEditComMsg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAcceptList.RemoveAll();  //初始化接收socket队列
	m_bListened=FALSE;  //没有开启网络服务
	m_bSerialPortOpened=FALSE; //没有打开串口
}

void C1120112108linheng_ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_ctrlComboComPort);
	DDX_Text(pDX, IDC_EDIT_NETMSG, m_strEditNetMsg);
	DDX_Text(pDX, IDC_EDIT_COMMSG, m_strEditComMsg);
	DDX_Text(pDX, IDC_EDIT_PORTNO, m_unEditPortNO);
	DDX_Control(pDX, IDC_CHECK_SENDDATA, m_ctrlCheckSendData);
}

BEGIN_MESSAGE_MAP(C1120112108linheng_ServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &C1120112108linheng_ServerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &C1120112108linheng_ServerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &C1120112108linheng_ServerDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &C1120112108linheng_ServerDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &C1120112108linheng_ServerDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// C1120112108linheng_ServerDlg 消息处理程序

BOOL C1120112108linheng_ServerDlg::OnInitDialog()
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
	m_ctrlComboComPort.SetCurSel(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C1120112108linheng_ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C1120112108linheng_ServerDlg::OnPaint()
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
HCURSOR C1120112108linheng_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C1120112108linheng_ServerDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pListenSocket=new CListenSocket();  //新建监听Socket
	if(m_pListenSocket->Create(m_unEditPortNO))
	{
		if(!m_pListenSocket->Listen(10))
		{
			AfxMessageBox("设置监听Socket失败",MB_ICONINFORMATION);
			delete m_pListenSocket; //释放指针空间
		}
		else
		{
			m_bListened=TRUE;
		}
	}
	else
	{
		AfxMessageBox("创建监听Socket失败",MB_ICONINFORMATION);
		delete m_pListenSocket; //释放指针空间
	}
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(!m_bListened);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(m_bListened);
}



void C1120112108linheng_ServerDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bListened) return;
	if(m_pListenSocket == NULL) return;
	m_pListenSocket->ShutDown(2);
	Sleep(50);
	m_pListenSocket->Close();
	m_pListenSocket = NULL;
	m_bListened = FALSE;	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(!m_bListened);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(m_bListened);
}

void C1120112108linheng_ServerDlg::UpdateMsgData()
{
	m_strEditNetMsg=m_strNetMsg;
	CFile mFile(_T("log.txt "), CFile::modeWrite);
	mFile.SeekToEnd(); 
	mFile.Write("\r\n"+ m_strEditNetMsg,strlen(m_strEditNetMsg) + 2); 
	mFile.Flush(); 
	mFile.Close(); 
	UpdateData(FALSE);   //更新网络通信信息
}




void C1120112108linheng_ServerDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPort=m_ctrlComboComPort.GetCurSel()+1; //得到串口号
	this->m_MyComm.Open(nPort,9600,0,8,0);//一个停止位
	if(m_MyComm.IsOpen())
	{
		AfxMessageBox("所选串口已打开");
		m_MyComm.SetWnd(this->m_hWnd);
		m_MyComm.SetNotifyNum(1); 
		m_bSerialPortOpened=true;

	}
	else
	{
		AfxMessageBox("没有发现此串口或被占用");
		m_bSerialPortOpened=FALSE;
	}
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(m_bSerialPortOpened);
}



void C1120112108linheng_ServerDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ctrlCheckSendData.GetCheck())
	{
		AfxMessageBox("请先关掉串口发送功能");
		return;
	}
	m_MyComm.Close();//关闭串口
	m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(m_bSerialPortOpened);
}

//检查串口是否打开，否则不能通过串口发送数据
void C1120112108linheng_ServerDlg::OnCheckSenddata() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckSendData.GetCheck())
	{
		if(!m_bSerialPortOpened)
		{
			AfxMessageBox("串口没有打开,请先打开串口");
			m_ctrlCheckSendData.SetCheck(0);
			return;
		}
	}
}

//通过串口发送数据
void C1120112108linheng_ServerDlg::SerialSendData(CString strSendData)
{
	if(!m_bSerialPortOpened) return;
	if(!m_ctrlCheckSendData.GetCheck()) return;
	m_MyComm.Write((LPCTSTR)strSendData);//发送数据
	m_strEditComMsg.Format("向COM%d发送：\r\n%s",
		m_ctrlComboComPort.GetCurSel()+1,strSendData);
	UpdateData(FALSE);
}




void C1120112108linheng_ServerDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strEditComMsg = "";
	m_strEditNetMsg = "";
	UpdateData(FALSE);
}
