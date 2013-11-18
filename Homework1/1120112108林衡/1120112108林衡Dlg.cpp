
// 1120112108�ֺ�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108�ֺ�.h"
#include "1120112108�ֺ�Dlg.h"
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


// CMy1120112108�ֺ�Dlg �Ի���




CMy1120112108�ֺ�Dlg::CMy1120112108�ֺ�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1120112108�ֺ�Dlg::IDD, pParent)
	, m_streditRXDATADISP(_T(""))
	, m_streditTXDATAINPUT(_T(""))
	, m_bSerialPortOpened(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bSerialPortOpened = false;
}

void CMy1120112108�ֺ�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RXDATADISP, m_streditRXDATADISP);
	DDX_Text(pDX, IDC_EDIT_TXDATAINPUT, m_streditTXDATAINPUT);
	DDX_Control(pDX, IDC_COMBO_PORTNO, m_ctrlcomboPORTNO);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ctrlcomboBAUDRATE);
	DDX_Control(pDX, IDC_COMBO_BYTESIZES, m_ctrlcomboBYTESIZES);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_ctrlcomboSTOPBITS);
}

BEGIN_MESSAGE_MAP(CMy1120112108�ֺ�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_PORTNO, &CMy1120112108�ֺ�Dlg::OnCbnSelchangeComboPortno)
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT, &CMy1120112108�ֺ�Dlg::OnBnClickedButtonOpenport)
	ON_BN_CLICKED(IDC_BUTTON_SENDDATA, &CMy1120112108�ֺ�Dlg::OnBnClickedButtonSenddata)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEPORT, &CMy1120112108�ֺ�Dlg::OnBnClickedButtonCloseport)
	ON_MESSAGE(ON_COM_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY_SENDBOX, &CMy1120112108�ֺ�Dlg::OnBnClickedButtonEmptySendbox)
	ON_BN_CLICKED(IDC_BUTTON_EMPTYREXBOX, &CMy1120112108�ֺ�Dlg::OnBnClickedButtonEmptyrexbox)
END_MESSAGE_MAP()


// CMy1120112108�ֺ�Dlg ��Ϣ�������

BOOL CMy1120112108�ֺ�Dlg::OnInitDialog()
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
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
	m_ctrlcomboPORTNO.SetCurSel(0);
	m_ctrlcomboBAUDRATE.SetCurSel(1);
	m_ctrlcomboBYTESIZES.SetCurSel(2);
	m_ctrlcomboSTOPBITS.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy1120112108�ֺ�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy1120112108�ֺ�Dlg::OnPaint()
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
HCURSOR CMy1120112108�ֺ�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy1120112108�ֺ�Dlg::OnCbnSelchangeComboPortno()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMy1120112108�ֺ�Dlg::OnBnClickedButtonOpenport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(_T("�����Ѿ��ɹ���"));
		m_CnComm.SetWnd(this->m_hWnd);
		m_bSerialPortOpened=TRUE;
	}
	else
	{
		AfxMessageBox(_T("���ڴ�ʧ��"));
		m_bSerialPortOpened=false;
	}
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);

}


void CMy1120112108�ֺ�Dlg::OnBnClickedButtonSenddata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bSerialPortOpened)
	{
		AfxMessageBox(_T("���ȴ򿪴���"));
		return;
	}
	UpdateData(TRUE);
	//AfxMessageBox(m_strEditTXDataInput);
	CStringA straTemp;
    straTemp = m_streditTXDATAINPUT; //UniCode�ַ�����ANSI�ַ���֮���ת��
	m_CnComm.Write(straTemp);
	//m_CnComm.Write(m_streditTXDATAINPUT);
	UpdateData(FALSE);

}


void CMy1120112108�ֺ�Dlg::OnBnClickedButtonCloseport()
{
	m_CnComm.Close();
	m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

LRESULT CMy1120112108�ֺ�Dlg::OnReceive(WPARAM port, LPARAM ch)
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



void CMy1120112108�ֺ�Dlg::OnBnClickedButtonEmptySendbox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_TXDATAINPUT,_T(""));
	m_streditTXDATAINPUT.Empty();
	UpdateData(false);
	
}


void CMy1120112108�ֺ�Dlg::OnBnClickedButtonEmptyrexbox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_RXDATADISP,_T(""));
	m_streditRXDATADISP.Empty();
	UpdateData(false);
}
