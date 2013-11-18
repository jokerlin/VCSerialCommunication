
// 1120112108�ֺ�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108�ֺ�.h"
#include "1120112108�ֺ�Dlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool iFirst = true, isE, isN; 
double currentLongitude, currentLatitude, currentAltitude, beforeLongitude, beforeLatitude, beforeAltitude;


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
	DDX_Control(pDX, IDC_EDIT_LATITUDE, m_ctrlEditLat);
	DDX_Control(pDX, IDC_EDIT_LONGITUDE, m_ctrlEditLon);
	DDX_Control(pDX, IDC_EDIT_SATNUM, m_ctrlEditSatNum);
	DDX_Control(pDX, IDC_EDIT_HDOP, m_ctrlEditHDOP);
	DDX_Control(pDX, IDC_EDIT_UTC, m_ctrlEditUTC);
	DDX_Control(pDX, IDC_EDIT_ALTITUDE, m_ctrlEditAlt);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_ctrlEditSpeed);
	DDX_Control(pDX, IDC_EDIT_HEADING, m_ctrlEditHead);
	DDX_Control(pDX, IDC_EDIT_RXDATADISP, m_ctrlEditRXDATADISP);
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
	static char FlagHead		= 0;						//���յ�ͷ��־
	static char FlagEnd			= 0;						//���յ�β��־
	static char FlagFinish		= 0;						//������ɱ�־
	static char DataCount		= 0;						//�������ݼ�����
	char		cTemp			= 0;
	
	int nBufflenth;
	int nReadlenth;

	UCHAR *pReadBuff;


	nBufflenth = m_CnComm.GetQueueCount();
	pReadBuff = new UCHAR[nBufflenth];
	nReadlenth = m_CnComm.Read(pReadBuff,nBufflenth);
	for(int i = 0; i<nReadlenth; i++)
	{
		cTemp = pReadBuff[i];
		CString str;
		str.Format(_T("%c"),	cTemp);
		int nLen=m_ctrlEditRXDATADISP.GetWindowTextLength();
		m_ctrlEditRXDATADISP.SetSel(nLen,nLen);
		m_ctrlEditRXDATADISP.ReplaceSel(str);
		nLen+=str.GetLength();

		//cTemp = ch;
		if('$' == cTemp)
		{
			FlagHead = 1;
			FlagEnd = 0;
			FlagFinish = 0;
			DataCount = 0;
			memset(m_chGPSDataFromReceiver,0,100);
			m_chGPSDataFromReceiver[DataCount++] = cTemp;
		}
		else
		{
			if(1 == FlagHead)
			{
				m_chGPSDataFromReceiver[DataCount++] = cTemp;
				if('*' == cTemp)
				{
					FlagEnd = 1;
				}
				if(1 == FlagEnd)
				{			

					char GPSHead[10];

					memset(GPSHead,0,10);
					memcpy(GPSHead,m_chGPSDataFromReceiver,6);
					
					if(0 == strcmp(GPSHead,"$GPGGA"))	
					{
						Proc_GPGGA(m_chGPSDataFromReceiver,DataCount-1);
						iFirst = false;
						return 0;
					}
					/*else if(0 == strcmp(GPSHead,"$GPRMC"))	
					{
						Proc_GPRMC(m_cGPSDataFromReceiver,DataCount-1);
					}
					else if(0 == strcmp(GPSHead,"$GPVTG"))
					{
						Proc_GPVTG(m_cGPSDataFromReceiver,DataCount-1);
					}*/
					else
					{
						FlagFinish = 1;
					}							
				}			
				if(DataCount >= 100)
				{
					FlagFinish = 1;
				}
			}
		}

		if(1 == FlagFinish)
		{
			FlagHead			 = 0;
			FlagFinish			 = 0;
			FlagEnd			 = 0;
			DataCount		 = 0;
			memset(m_chGPSDataFromReceiver,0,100);	
		}
	}

	delete [] pReadBuff;

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


void CMy1120112108�ֺ�Dlg::Proc_GPGGA(char* chBuff, int nNum)
{
	double dTemp = 0.0;
	double dTemp1 = 0.0,dTemp2 = 0.0;
	UINT  unTemp = 0;
	long  lTemp = 0;
	CString strTemp;
	 

	int i = 0;
	int j = 0;
	int nGPSCommaNumber = 0;
	char chGPSDataTemp[15];

	memset(chGPSDataTemp,0,15);
	m_ctrlEditAlt.SetWindowTextW(NULL);	
	m_ctrlEditLat.SetWindowTextW(NULL);	
	m_ctrlEditLon.SetWindowTextW(NULL);	
	m_ctrlEditSatNum.SetWindowTextW(NULL);	
	m_ctrlEditHDOP.SetWindowTextW(NULL);	
	m_ctrlEditUTC.SetWindowTextW(NULL);		
	m_ctrlEditSpeed.SetWindowTextW(NULL);	
	m_ctrlEditHead.SetWindowTextW(NULL);							
	while(i++ <= nNum)
	{
								
		if(chBuff[i] == ',')		//������
		{
			j = 0;
			nGPSCommaNumber++;
			switch(nGPSCommaNumber)
			{
				case 1: // $GPGGA                                                          
					memset(chGPSDataTemp,0,15);	
					break;
				case 2: // UTC
					lTemp = atol(chGPSDataTemp);
					strTemp.Format(_T("%d:%d:%d"),(lTemp/10000),(lTemp%10000/100),(lTemp%100));
					m_ctrlEditUTC.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);	
					break;
				case 3: // Latitude
					dTemp=atof(chGPSDataTemp);                                              
					unTemp = (UINT)(dTemp/100);
					dTemp1 = unTemp + (dTemp - unTemp * 100.0) / 60.0;
					memset(chGPSDataTemp,0,15);
					break;
				case 4: // Latitude hemisphere
					strTemp.Format(_T("%C:%.7f"),chGPSDataTemp[0],dTemp1);
				    
					if (chGPSDataTemp[0] == 'N') isN = true;
					else isN = false;
					beforeLatitude = currentLatitude;
					currentLatitude = dTemp1;

					m_ctrlEditLat.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);
					break;
				case 5: // Longitude
					dTemp=atof(chGPSDataTemp);                                              
					unTemp = (UINT)(dTemp/100);
					dTemp1 = unTemp + (dTemp - unTemp * 100.0) / 60.0;
					memset(chGPSDataTemp,0,15);
					break;
				case 6: // Longitude hemisphere
					strTemp.Format(_T("%C:%.7f"),chGPSDataTemp[0],dTemp1);
					
					if (chGPSDataTemp[0] == 'E') isE = true;
					else isE = false;
					beforeLongitude = currentLongitude;
					currentLongitude = dTemp1;
					
					m_ctrlEditLon.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);
					break;
				case 7: // GPS quality
					//unTemp = atoi(GPSDataTemp);
					//strTemp.Format(_T("%d"),unTemp);
					//m_ctrlEditQua.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);
					break;
				case 8: // GPS number
					unTemp = atoi(chGPSDataTemp);
					strTemp.Format(_T("%d"),unTemp);
					m_ctrlEditSatNum.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);
					break;
				case 9: // HDOP
					dTemp = atof(chGPSDataTemp);
					strTemp.Format(_T("%.1f"),dTemp);
					m_ctrlEditHDOP.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);
					break;
				case 10: // Antenna height
					dTemp = atof(chGPSDataTemp);
					strTemp.Format(_T("%.1f"),dTemp);
					
					currentAltitude = dTemp;
					
					m_ctrlEditAlt.SetWindowTextW(strTemp);
					memset(chGPSDataTemp,0,15);
					break;
				
									
				default: break;
			}
		}
		else 
		{
			if(nGPSCommaNumber <=10 ) 
				chGPSDataTemp[j++] = chBuff[i];
		}
	}	

	double dDistance;//��ʱ������ߵľ���
	if (!iFirst)
	{
		if(!isE) currentLongitude=-currentLongitude;
		if(!isN) currentLatitude =-currentLatitude;
		
		double diffLongitude=currentLongitude-beforeLongitude;
		double diffLatitude=currentLatitude-beforeLatitude;
		double diffAltitude=currentAltitude-beforeAltitude;

		if(diffLongitude>0){
			if(diffLatitude>0)
			m_ctrlEditHead.SetWindowTextW(_T("����"));
			else if(abs(diffLatitude)<1E-6)
				m_ctrlEditHead.SetWindowTextW(_T("����"));
			else m_ctrlEditHead.SetWindowTextW(_T("����"));
		}
		else if(diffLongitude<0&&currentLatitude<0){
			if(diffLatitude>0)
			m_ctrlEditHead.SetWindowTextW(_T("����"));
			else if(abs(diffLatitude)<1E-6)
				m_ctrlEditHead.SetWindowTextW(_T("����"));
			else m_ctrlEditHead.SetWindowTextW(_T("����"));
		}
		else{
			if(diffLatitude>0)
			m_ctrlEditHead.SetWindowTextW(_T("����"));
			else if(abs(diffLatitude)<1E-6)
				m_ctrlEditHead.SetWindowTextW(_T("static"));
			else m_ctrlEditHead.SetWindowTextW(_T("����"));
		}
		double EARTH_RADII = 6378100;
		dDistance=sqrt(2*EARTH_RADII*EARTH_RADII*(1-cos(diffLongitude / 180 * 3.14)*cos(diffLatitude / 180 * 3.14))+diffAltitude*diffAltitude);
		CString strSuDu;
		strSuDu.Format(_T("%.2f"),dDistance);

		m_ctrlEditSpeed.SetWindowTextW(strSuDu);
	}
	FILE *fp;
   
	fp  = fopen( "GPGGA.txt","a+");//���ļ�
	if( fp )
	{
		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 
		fprintf(fp, "%4d/%02d/%02d %02d:%02d:%02d\n",
					sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond); 
		fprintf(fp,"%s\n",chBuff);	
		fclose(fp);
		  
	}
	else
	{
		AfxMessageBox(_T("The file 'GPGGA.txt' was not opened"));
	}

}
