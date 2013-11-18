
// 1120112108linheng_ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108linheng_Server.h"
#include "1120112108linheng_ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C1120112108linheng_ServerDlg �Ի���



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
	m_pAcceptList.RemoveAll();  //��ʼ������socket����
	m_bListened=FALSE;  //û�п����������
	m_bSerialPortOpened=FALSE; //û�д򿪴���
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


// C1120112108linheng_ServerDlg ��Ϣ�������

BOOL C1120112108linheng_ServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ctrlComboComPort.SetCurSel(0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C1120112108linheng_ServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C1120112108linheng_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C1120112108linheng_ServerDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_pListenSocket=new CListenSocket();  //�½�����Socket
	if(m_pListenSocket->Create(m_unEditPortNO))
	{
		if(!m_pListenSocket->Listen(10))
		{
			AfxMessageBox("���ü���Socketʧ��",MB_ICONINFORMATION);
			delete m_pListenSocket; //�ͷ�ָ��ռ�
		}
		else
		{
			m_bListened=TRUE;
		}
	}
	else
	{
		AfxMessageBox("��������Socketʧ��",MB_ICONINFORMATION);
		delete m_pListenSocket; //�ͷ�ָ��ռ�
	}
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(!m_bListened);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(m_bListened);
}



void C1120112108linheng_ServerDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	UpdateData(FALSE);   //��������ͨ����Ϣ
}




void C1120112108linheng_ServerDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nPort=m_ctrlComboComPort.GetCurSel()+1; //�õ����ں�
	this->m_MyComm.Open(nPort,9600,0,8,0);//һ��ֹͣλ
	if(m_MyComm.IsOpen())
	{
		AfxMessageBox("��ѡ�����Ѵ�");
		m_MyComm.SetWnd(this->m_hWnd);
		m_MyComm.SetNotifyNum(1); 
		m_bSerialPortOpened=true;

	}
	else
	{
		AfxMessageBox("û�з��ִ˴��ڻ�ռ��");
		m_bSerialPortOpened=FALSE;
	}
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(m_bSerialPortOpened);
}



void C1120112108linheng_ServerDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_ctrlCheckSendData.GetCheck())
	{
		AfxMessageBox("���ȹص����ڷ��͹���");
		return;
	}
	m_MyComm.Close();//�رմ���
	m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(m_bSerialPortOpened);
}

//��鴮���Ƿ�򿪣�������ͨ�����ڷ�������
void C1120112108linheng_ServerDlg::OnCheckSenddata() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckSendData.GetCheck())
	{
		if(!m_bSerialPortOpened)
		{
			AfxMessageBox("����û�д�,���ȴ򿪴���");
			m_ctrlCheckSendData.SetCheck(0);
			return;
		}
	}
}

//ͨ�����ڷ�������
void C1120112108linheng_ServerDlg::SerialSendData(CString strSendData)
{
	if(!m_bSerialPortOpened) return;
	if(!m_ctrlCheckSendData.GetCheck()) return;
	m_MyComm.Write((LPCTSTR)strSendData);//��������
	m_strEditComMsg.Format("��COM%d���ͣ�\r\n%s",
		m_ctrlComboComPort.GetCurSel()+1,strSendData);
	UpdateData(FALSE);
}




void C1120112108linheng_ServerDlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strEditComMsg = "";
	m_strEditNetMsg = "";
	UpdateData(FALSE);
}
