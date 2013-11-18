
// CMy1120112108LinHengDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108LinHeng.h"
#include "CMy1120112108LinHengDlg.h"
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


// CMy1120112108LinHengDlg �Ի���



CMy1120112108LinHengDlg::CMy1120112108LinHengDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1120112108LinHengDlg::IDD, pParent)
	, m_strEditRXDataDisp(_T(""))
	, m_strEditTXDataInput(_T(""))
	, m_unEditPosition(0)
	, m_unEditPosition2(0)
	, m_unEditVelocity(0)
	, m_unEditVelocity2(0)
	, m_strEditDispData2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//�ڹ��캯���еı�����ʼ��
	m_hIconRed=AfxGetApp()->LoadIcon(IDI_ICON_RED);
	m_hIconOff=AfxGetApp()->LoadIcon(IDI_ICON_OFF);
	m_bSerialPortOpened=FALSE;  //��1������û�д�
	m_bSerialPortOpened2=FALSE; //��2������û�д�
	m_unPort1=1;  //��1�����ڴ��ںų�ֵ��ΪCOM1
	m_unPort2=2; //��2�����ڴ��ںų�ֵ��ΪCOM2
}

void CMy1120112108LinHengDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RXDATADISP, m_strEditRXDataDisp);
	DDX_Text(pDX, IDC_EDIT_TXDATAINPUT, m_strEditTXDataInput);
	DDX_Control(pDX, IDC_COMBO_PORTNO, m_ctrlComboPortNO);
	DDX_Control(pDX, IDC_STATIC_ICONS1, m_ctrlStaticIconS1);
	DDX_Control(pDX, IDC_STATIC_ICONS2, m_ctrlStaticIconS2);
	DDX_Control(pDX, IDC_STATIC_ICONS3, m_ctrlStaticIconS3);
	DDX_Control(pDX, IDC_STATIC_ICONS4, m_ctrlStaticIconS4);
	DDX_Control(pDX, IDC_STATIC_ICONS5, m_ctrlStaticIconS5);
	DDX_Control(pDX, IDC_STATIC_ICONS6, m_ctrlStaticIconS6);
	DDX_Control(pDX, IDC_STATIC_ICONS7, m_ctrlStaticIconS7);
	DDX_Control(pDX, IDC_STATIC_ICONS8, m_ctrlStaticIconS8);
	DDX_Control(pDX, IDC_CHECK_SWITCH1, m_ctrlCheckSwitch1);
	DDX_Control(pDX, IDC_CHECK_SWITCH2, m_ctrlCheckSwitch2);
	DDX_Control(pDX, IDC_CHECK_SWITCH4, m_ctrlCheckSwitch4);
	DDX_Control(pDX, IDC_CHECK_SWITCH5, m_ctrlCheckSwitch5);
	DDX_Control(pDX, IDC_CHECK_SWITCH6, m_ctrlCheckSwitch6);
	DDX_Control(pDX, IDC_CHECK_SWITCH7, m_ctrlCheckSwitch7);
	DDX_Control(pDX, IDC_CHECK_SWITCH8, m_ctrlCheckSwitch8);
	DDX_Control(pDX, IDC_COMBO_PORTNO2, m_ctrlComboPortNO2);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_unEditPosition);
	DDV_MinMaxUInt(pDX, m_unEditPosition, 0, 31);
	DDX_Text(pDX, IDC_EDIT_POSITION2, m_unEditPosition2);
	DDV_MinMaxUInt(pDX, m_unEditPosition2, 0, 31);
	DDX_Text(pDX, IDC_EDIT_VELOCITY, m_unEditVelocity);
	DDV_MinMaxUInt(pDX, m_unEditVelocity, 0, 120);
	DDX_Text(pDX, IDC_EDIT_VELOCITY2, m_unEditVelocity2);
	DDX_Text(pDX, IDC_EDIT_DISPDATA2, m_strEditDispData2);
	DDX_Control(pDX, IDC_CHECK_SWITCH3, m_ctrlCheckSwitch3);
}

BEGIN_MESSAGE_MAP(CMy1120112108LinHengDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT, &CMy1120112108LinHengDlg::OnBnClickedButtonOpenport)
	ON_BN_CLICKED(SENDDATA, &CMy1120112108LinHengDlg::OnBnClickedSenddata)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEPORT, &CMy1120112108LinHengDlg::OnBnClickedButtonCloseport)
	ON_MESSAGE(ON_COM_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT2, &CMy1120112108LinHengDlg::OnBnClickedButtonOpenport2)
END_MESSAGE_MAP()


// CMy1120112108LinHengDlg ��Ϣ��������

BOOL CMy1120112108LinHengDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	m_ctrlComboPortNO.SetCurSel(0);
	m_ctrlComboPortNO2.SetCurSel(1);
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_OPENPORT2)->EnableWindow(!m_bSerialPortOpened2);
	GetDlgItem(IDC_BUTTON_CLOSEPORT2)->EnableWindow(m_bSerialPortOpened2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy1120112108LinHengDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy1120112108LinHengDlg::OnPaint()
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
HCURSOR CMy1120112108LinHengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy1120112108LinHengDlg::OnBnClickedButtonOpenport()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int nPortNo = m_ctrlComboPortNO.GetCurSel()+1;
	m_CnComm.Open(nPortNo);
	if(m_CnComm.IsOpen())
	{
		//AfxMessageBox(_T("�����Ѿ��ɹ���"));
		m_CnComm.SetWnd(this->m_hWnd);
		m_bSerialPortOpened=TRUE;
		m_unPort1=nPortNo; //�����Ա������¼�򿪵Ĵ��ںţ�����ִ����������ں�
	}
	else
	{
		AfxMessageBox(_T("���ڴ�ʧ��"));
		m_bSerialPortOpened=false;
	}
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
}


void CMy1120112108LinHengDlg::OnBnClickedSenddata()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if(!m_bSerialPortOpened) //��鴮���Ƿ��
	{
		AfxMessageBox(_T("����û�д�"));
		return; 
	}
	UpdateData(TRUE); //����༭���е�����
	CString strSend=_T(""); //Ҫ���͵�NEMA�ַ���
	//���¶���8�����ص�����״̬
	for(int i=1;i<=8;i++)
	{
		if(GetSwitchStatus(i))
			strSend+='1';
		else
			strSend+='0';
	}
	CString strTemp;
	strTemp.Format(_T("%02d"),m_unEditPosition);
	strSend+=strTemp;
	strTemp.Format(_T("%03d"),m_unEditVelocity);
	strSend+=strTemp;
	SendNMEAData(strSend);
}


void CMy1120112108LinHengDlg::OnBnClickedButtonCloseport()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_CnComm.Close();
	m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
}

#define CR 0X0D    //�س�
#define LF 0X0A    //����
LRESULT CMy1120112108LinHengDlg::OnReceive(WPARAM port, LPARAM ch)
{
	static unsigned char com1rec[4];
	static char checksum=0,checksum1=0;
	static int count1=0;//,count2=0,count3=0;
	static unsigned char buf[20]; 
	static char c1,c2;    //���ڼ����ByteУ��
	static int flag;     //���ڽ��ս׶α��
	static int twoflag=0;
	char str[50];
	if (port == m_unPort1)
	{
		int bufferlength,readlength;
		unsigned char* buffer;
		bufferlength=m_CnComm.GetQueueCount();
		buffer=new unsigned char[bufferlength];
		readlength=m_CnComm.Read(buffer,bufferlength);
		for(int j=0;j<4;j++)
		{
			com1rec[j]=0;
		}
		for(int i=0;i<readlength;i++)
		{
			unsigned char checksum1=0;
			for(int j=0;j<3;j++)
			{
				com1rec[j]=com1rec[j+1];
			}
			com1rec[3]=buffer[i];
			//unsigned char temp=com1rec[0]>>7;
			//if((temp-1)==0)
			com1rec[0]|=0x80;
			if((com1rec[0]&0x80)==0x80)
			{
				checksum1=com1rec[0];
				for(int j=1;j<=3;j++)
				{
					checksum1=checksum1^com1rec[j];
				}
				if(checksum1==0x80)
				{
					CString str;
					m_strEditRXDataDisp = "���յ��ļ�ͨ��Э���ֽ�Ϊ��";
					for(int i=0;i<4;i++)
					{
						str.Format("%.2x ",com1rec[i]);
						m_strEditRXDataDisp += str;
					}
					UpdateData(false);
				}
			}

			else
			{
				m_strEditRXDataDisp = "����У�����";
				UpdateData(false);
			}
		}
		delete[] buffer;
	}
	if (port == m_unPort2)
	{
		m_CnComm2.ReadString(str,20);
		m_strPortRXData2 += str;	
		for (int i_count=0;i_count<20;i_count++)
		{
			switch(str[i_count])
			{
			case '$':
				checksum=0;			//��ʼ����CheckSum
				flag=0;
				break;
			case '*':  //��Ч���ݽ���������$��*֮�����ݵİ�ByteУ��ֵ��
				flag=2;
				c2=checksum & 0x0f;	c1=((checksum >> 4) & 0x0f);
				if (c1 < 10) c1+= '0';	else c1 += 'A' - 10;
				if (c2 < 10) c2+= '0';	else c2 += 'A' - 10;
				break;
			case CR:   //��������ϣ�����������
				break;
			case LF:   //���ݰ������һ���ַ�
				m_strPortRXData2.Empty();
				break;
			default:
				if(flag>0)  //ע�⣺ֻ���ڽ��յ�'*'��flag�Ŵ���0
				{
					m_strCheckSum2 += str[i_count];  
					if(flag==1) 
					{

						CString strCheck=_T("");
						strCheck.Format(_T("%c%c"),c1,c2);
						//AfxMessageBox(strCheck);
						if(strCheck!=m_strCheckSum2)  //У����㲻��ȷ��˵���������ݳ���
						{
							AfxMessageBox(_T("У�鲻��ȷ"));
							m_strPortRXData2.Empty();
						}
						else  //У�������ȷ��������
						{
							//AfxMessageBox(_T("У����ȷ"));
							CString strSwitchSetData;
							strSwitchSetData = m_strPortRXData2.Mid(1,8);//Mid(   int   nFirst,   int   nCount   )   const; 
							//���������źŵ�״̬
							for(int i=0;i<8;i++)//����һλ
							{
								if(strSwitchSetData.Mid(i,1)=="1")
									SetSwitchStatus(i+1,TRUE);
								else
									SetSwitchStatus(i+1,FALSE);
							}
							//����ȡ��λ�����ٶ�����
							CString strTemp;
							strTemp = m_strPortRXData2.Mid(9,5);
							char *temp=(char*)((LPCTSTR)strTemp);
							char tbuf[4];
							tbuf[0]=temp[0]; tbuf[1]=temp[1]; tbuf[2]=0;
							m_unEditPosition2 = atoi(tbuf);  //�õ�λ��״ֵ̬
							tbuf[0]=temp[2]; tbuf[1]=temp[3]; 
							tbuf[2]=temp[4]; tbuf[3]=0;
							m_unEditVelocity2 = atoi(tbuf);  //�õ��ٶ�ֵ
							//�����յ������ݰ�������ʾ
							m_strEditDispData2 = _T("���յ�NMEA���ݰ���")+m_strPortRXData2;
							//����׼������"���Զ���ͨ��Э��"���ݰ�
							unsigned char ucChar[4];
							//���ֽ�
							ucChar[0]=0x80;   //���ֽ����λ��1
							if(strSwitchSetData.Mid(0,1)=="1")  // ����1״̬
								ucChar[0] |= 0x40;            //0100 0000 
							else
								ucChar[0] &= 0xBF;	          //1011 1111				
							if(strSwitchSetData.Mid(1,1)=="1")  // ����2״̬
								ucChar[0] |= 0x20;            //0010 0000 
							else
								ucChar[0] &= 0xDF;	          //1101 1111
							if(m_unEditPosition2>31)      //��λ��ֵ������ֵ
								m_unEditPosition2=31;
							ucChar[0] &= 0xE0;    //�����ֽڵĵ�5λ��0
							ucChar[0] += m_unEditPosition2; //�ټ���λ��ֵ
							ucChar[3] = ucChar[0];    //ͬʱ����У��ֵ
							//�ڶ��ֽ�
							unsigned char ucTemp=0x40;
							for(int i=0; i<6; i++)
							{
								if(strSwitchSetData.Mid(2+i,1)=="1")  
									ucChar[1] |= ucTemp;             
								else
									ucChar[1] &= (~ucTemp);
								ucTemp >>= 1;
							}
							ucChar[1] &= 0x7F; //ǰ��������ô�����㣬��������䱣֤һ�����λΪ0
							ucChar[3] ^= ucChar[1];   //����У��ֵ
							////�����ֽ�
							if(m_unEditVelocity2>120)
								m_unEditVelocity2=120;
							ucChar[2] = m_unEditVelocity2;
							ucChar[3] ^= ucChar[2];   //����У��ֵ
							////�����ֽ�
							ucChar[3] &= 0x7F;
							CString strTemp1;
							strTemp=   _T("��ͨ������Ϊ: ");
							for(int j=0;j<4;j++)
							{
								strTemp1.Format(_T("0x%02X"),ucChar[j]);
								strTemp +=  strTemp1 + _T(",");
							}
							m_strEditDispData2 += strTemp;

							UpdateData(FALSE);
							if(m_bSerialPortOpened2)	 m_CnComm2.Write(ucChar,4);
						}
						m_strCheckSum2.Empty();
					}
					//��'*'���գ�flag=2,1�μ�1���������ý����ݰ���У��ֵ������m_strChecksum2��
					flag--;  
				}
				else
					checksum= checksum^str[i_count];  //��flag<=0ʱ������У��ֵ
				break;
			}

		}
	}

	return 0;
}


void CMy1120112108LinHengDlg::SetSwitchStatus(unsigned int unSwitch, bool bStatus)
{
	if(bStatus)   //���ÿ��ش�״̬
	{
		switch(unSwitch) {
		case 1: 
			m_ctrlStaticIconS1.SetIcon(m_hIconRed);
			break;
		case 2: 
			m_ctrlStaticIconS2.SetIcon(m_hIconRed);
			break;
		case 3: 
			m_ctrlStaticIconS3.SetIcon(m_hIconRed);
			break;
		case 4: 
			m_ctrlStaticIconS4.SetIcon(m_hIconRed);
			break;
		case 5: 
			m_ctrlStaticIconS5.SetIcon(m_hIconRed);
			break;
		case 6: 
			m_ctrlStaticIconS6.SetIcon(m_hIconRed);
			break;
		case 7: 
			m_ctrlStaticIconS7.SetIcon(m_hIconRed);
			break;
		case 8: 
			m_ctrlStaticIconS8.SetIcon(m_hIconRed);
			break;
			/*	case 9: 
			m_ctrlStaticIconS9.SetIcon(m_hIconRed);
			break;*/
		default:
			break;
		}
	}
	else     //���ÿ��عر�״̬
	{
		switch(unSwitch) {
		case 1: 
			m_ctrlStaticIconS1.SetIcon(m_hIconOff);
			break;
		case 2: 
			m_ctrlStaticIconS2.SetIcon(m_hIconOff);
			break;
		case 3: 
			m_ctrlStaticIconS3.SetIcon(m_hIconOff);
			break;
		case 4: 
			m_ctrlStaticIconS4.SetIcon(m_hIconOff);
			break;
		case 5: 
			m_ctrlStaticIconS5.SetIcon(m_hIconOff);
			break;
		case 6: 
			m_ctrlStaticIconS6.SetIcon(m_hIconOff);
			break;
		case 7: 
			m_ctrlStaticIconS7.SetIcon(m_hIconOff);
			break;
		case 8: 
			m_ctrlStaticIconS8.SetIcon(m_hIconOff);
			break;
			/*case 9: 
			m_ctrlStaticIconS9.SetIcon(m_hIconOff);
			break;*/
		default:
			break;
		}
	}

}


bool CMy1120112108LinHengDlg::GetSwitchStatus(unsigned int unSwitch)
{
	BOOL bStatus=FALSE;
	switch(unSwitch) {
	case 1:
		bStatus = m_ctrlCheckSwitch1.GetCheck();
		break;
	case 2:
		bStatus = m_ctrlCheckSwitch2.GetCheck();
		break;
	case 3:
		bStatus = m_ctrlCheckSwitch3.GetCheck();
		break;
	case 4:
		bStatus = m_ctrlCheckSwitch4.GetCheck();
		break;
	case 5:
		bStatus = m_ctrlCheckSwitch5.GetCheck();
		break;
	case 6:
		bStatus = m_ctrlCheckSwitch6.GetCheck();
		break;
	case 7:
		bStatus = m_ctrlCheckSwitch7.GetCheck();
		break;
	case 8:
		bStatus = m_ctrlCheckSwitch8.GetCheck();
		break;
		/*	case 9:
		bStatus = m_ctrlCheckSwitch9.GetCheck();
		break;*/
	default:
		break;
	}
	return bStatus;

}


void CMy1120112108LinHengDlg::OnBnClickedButtonOpenport2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int nPortNo = m_ctrlComboPortNO2.GetCurSel()+1;
	m_CnComm2.Open(nPortNo);
	if(m_CnComm2.IsOpen())
	{
		//AfxMessageBox(_T("�����Ѿ��ɹ���"));
		m_CnComm2.SetWnd(this->m_hWnd);
		m_bSerialPortOpened2=TRUE;
		m_unPort2=nPortNo; //�����Ա������¼�򿪵Ĵ��ںţ�����ִ����������ں�
	}
	else
	{
		AfxMessageBox(_T("���ڴ�ʧ��"));
		m_bSerialPortOpened2=false;
	}
	GetDlgItem(IDC_BUTTON_OPENPORT2)->EnableWindow(!m_bSerialPortOpened2);
	GetDlgItem(IDC_BUTTON_CLOSEPORT2)->EnableWindow(m_bSerialPortOpened2);
}


void CMy1120112108LinHengDlg::SendNMEAData(CString& strData)
{
	char checksum=0,cr=13,ln=10;
	char c1,c2; //2�� ��Bype У��ֵ 
	for(int i=0;i<strData.GetLength();i++)
		checksum = checksum^strData[i];
	c2=checksum & 0x0F;	c1=((checksum >> 4) & 0x0F);
	if (c1 < 10) c1+= '0';	else c1 += 'A' - 10;
	if (c2 < 10) c2+= '0';	else c2 += 'A' - 10;
	CString strNMEAData;
	//���ϰ�ͷ��β��У��ֵ�ͻس����з�
	strNMEAData=_T("$")+ strData +_T("*")+c1+c2+cr+ln; 
	//���¼��г���ز�ͨ�ã����Լ��ĳ�����ע���޸�
	m_CnComm.Write((LPCTSTR)strNMEAData);
	m_strEditTXDataInput.Format(_T("���͵����ݰ�Ϊ��%s"),strNMEAData);
	UpdateData(FALSE);  //�ڷ�����ʾ�༭������ʾ���͵����ݰ� 
}