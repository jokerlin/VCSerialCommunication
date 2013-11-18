
// 1120112108linheng_ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108linheng_Client.h"
#include "1120112108linheng_ClientDlg.h"
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


// C1120112108linheng_ClientDlg �Ի���



C1120112108linheng_ClientDlg::C1120112108linheng_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C1120112108linheng_ClientDlg::IDD, pParent)
	, m_strEditIPAddr(_T(""))
	, m_unEditPortNO(0)
	, m_strEditSendData(_T(""))
	, m_strEditRecvData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strEditIPAddr = _T("127.0.0.1"); //127.0.0.1 �Ǳ���IP ��ַ��Ҳ�������뱾������ʵIP ��ַ
	m_unEditPortNO = 5050; //ע���ˣ������װ�˲�������ǽ��Ҫ����Ӧ�˿ڴ�
	m_strEditRecvData = _T("");
	m_strEditSendData = _T("");
	m_bLinked=FALSE;   //�����Ƿ����ӣ���ʼ״̬��Ϊ��
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


// C1120112108linheng_ClientDlg ��Ϣ�������

BOOL C1120112108linheng_ClientDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C1120112108linheng_ClientDlg::OnPaint()
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
HCURSOR C1120112108linheng_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C1120112108linheng_ClientDlg::OnBnClickedButtonLink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_pMySocket=new MySocket;
	m_pMySocket->Create();
	m_bLinked=m_pMySocket->Connect(m_strEditIPAddr, m_unEditPortNO);
	if(!m_bLinked)
	{
		AfxMessageBox("���ӷ�����ʧ��");
	}
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(!m_bLinked);
	GetDlgItem(IDC_BUTTON_UNLINK)->EnableWindow(m_bLinked);
}



void C1120112108linheng_ClientDlg::OnBnClickedButtonUnlink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bLinked) return; //���û�����ӣ��ͷ���
	if(m_pMySocket->ShutDown(2))//�رս����뷢��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bLinked)
	{
		AfxMessageBox("û����������");
		return;
	}
	UpdateData(TRUE);
	CTime t = CTime::GetCurrentTime();
	int d=t.GetDay(); //��ü���
	int y=t.GetYear(); //��ȡ���
	int m=t.GetMonth(); //��ȡ��ǰ�·�
	int h=t.GetHour(); //��ȡ��ǰΪ��ʱ
	int mm=t.GetMinute(); //��ȡ����
	int s=t.GetSecond(); //��ȡ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strEditSendData = "";
	m_strEditRecvData = "";
	UpdateData(FALSE);
}
