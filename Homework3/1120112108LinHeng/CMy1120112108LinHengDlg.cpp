
// CMy1120112108LinHengDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1120112108LinHeng.h"
#include "CMy1120112108LinHengDlg.h"
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


// CMy1120112108LinHengDlg 对话框



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
	//在构造函数中的变量初始化
	m_hIconRed=AfxGetApp()->LoadIcon(IDI_ICON_RED);
	m_hIconOff=AfxGetApp()->LoadIcon(IDI_ICON_OFF);
	m_bSerialPortOpened=FALSE;  //第1个串口没有打开
	m_bSerialPortOpened2=FALSE; //第2个串口没有打开
	m_unPort1=1;  //第1个串口串口号初值设为COM1
	m_unPort2=2; //第2个串口串口号初值设为COM2
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


// CMy1120112108LinHengDlg 消息处理程序

BOOL CMy1120112108LinHengDlg::OnInitDialog()
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
	m_ctrlComboPortNO.SetCurSel(0);
	m_ctrlComboPortNO2.SetCurSel(1);
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_OPENPORT2)->EnableWindow(!m_bSerialPortOpened2);
	GetDlgItem(IDC_BUTTON_CLOSEPORT2)->EnableWindow(m_bSerialPortOpened2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1120112108LinHengDlg::OnPaint()
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
HCURSOR CMy1120112108LinHengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy1120112108LinHengDlg::OnBnClickedButtonOpenport()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPortNo = m_ctrlComboPortNO.GetCurSel()+1;
	m_CnComm.Open(nPortNo);
	if(m_CnComm.IsOpen())
	{
		//AfxMessageBox(_T("串口已经成功打开"));
		m_CnComm.SetWnd(this->m_hWnd);
		m_bSerialPortOpened=TRUE;
		m_unPort1=nPortNo; //用类成员变量记录打开的串口号，函数执行完后保留串口号
	}
	else
	{
		AfxMessageBox(_T("串口打开失败"));
		m_bSerialPortOpened=false;
	}
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
}


void CMy1120112108LinHengDlg::OnBnClickedSenddata()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bSerialPortOpened) //检查串口是否打开
	{
		AfxMessageBox(_T("串口没有打开"));
		return; 
	}
	UpdateData(TRUE); //读入编辑框中的数据
	CString strSend=_T(""); //要发送的NEMA字符串
	//以下读入8个开关的设置状态
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
	// TODO: 在此添加控件通知处理程序代码
	m_CnComm.Close();
	m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPENPORT)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSEPORT)->EnableWindow(m_bSerialPortOpened);
}

#define CR 0X0D    //回车
#define LF 0X0A    //换行
LRESULT CMy1120112108LinHengDlg::OnReceive(WPARAM port, LPARAM ch)
{
	static unsigned char com1rec[4];
	static char checksum=0,checksum1=0;
	static int count1=0;//,count2=0,count3=0;
	static unsigned char buf[20]; 
	static char c1,c2;    //用于计算半Byte校验
	static int flag;     //用于接收阶段标记
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
					m_strEditRXDataDisp = "接收到的简单通信协议字节为：";
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
				m_strEditRXDataDisp = "接收校验出错";
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
				checksum=0;			//开始计算CheckSum
				flag=0;
				break;
			case '*':  //有效数据结束，可以$和*之间数据的半Byte校验值了
				flag=2;
				c2=checksum & 0x0f;	c1=((checksum >> 4) & 0x0f);
				if (c1 < 10) c1+= '0';	else c1 += 'A' - 10;
				if (c2 < 10) c2+= '0';	else c2 += 'A' - 10;
				break;
			case CR:   //这句必须加上，否则会出错的
				break;
			case LF:   //数据包的最后一个字符
				m_strPortRXData2.Empty();
				break;
			default:
				if(flag>0)  //注意：只有在接收到'*'后，flag才大于0
				{
					m_strCheckSum2 += str[i_count];  
					if(flag==1) 
					{

						CString strCheck=_T("");
						strCheck.Format(_T("%c%c"),c1,c2);
						//AfxMessageBox(strCheck);
						if(strCheck!=m_strCheckSum2)  //校验计算不正确，说明接收数据出错
						{
							AfxMessageBox(_T("校验不正确"));
							m_strPortRXData2.Empty();
						}
						else  //校验计算正确则处理数据
						{
							//AfxMessageBox(_T("校验正确"));
							CString strSwitchSetData;
							strSwitchSetData = m_strPortRXData2.Mid(1,8);//Mid(   int   nFirst,   int   nCount   )   const; 
							//以下设置信号灯状态
							for(int i=0;i<8;i++)//少了一位
							{
								if(strSwitchSetData.Mid(i,1)=="1")
									SetSwitchStatus(i+1,TRUE);
								else
									SetSwitchStatus(i+1,FALSE);
							}
							//以下取出位置与速度数据
							CString strTemp;
							strTemp = m_strPortRXData2.Mid(9,5);
							char *temp=(char*)((LPCTSTR)strTemp);
							char tbuf[4];
							tbuf[0]=temp[0]; tbuf[1]=temp[1]; tbuf[2]=0;
							m_unEditPosition2 = atoi(tbuf);  //得到位置状态值
							tbuf[0]=temp[2]; tbuf[1]=temp[3]; 
							tbuf[2]=temp[4]; tbuf[3]=0;
							m_unEditVelocity2 = atoi(tbuf);  //得到速度值
							//将接收到的数据包内容显示
							m_strEditDispData2 = _T("接收到NMEA数据包：")+m_strPortRXData2;
							//下面准备发送"简单自定义通信协议"数据包
							unsigned char ucChar[4];
							//首字节
							ucChar[0]=0x80;   //首字节最高位置1
							if(strSwitchSetData.Mid(0,1)=="1")  // 开关1状态
								ucChar[0] |= 0x40;            //0100 0000 
							else
								ucChar[0] &= 0xBF;	          //1011 1111				
							if(strSwitchSetData.Mid(1,1)=="1")  // 开关2状态
								ucChar[0] |= 0x20;            //0010 0000 
							else
								ucChar[0] &= 0xDF;	          //1101 1111
							if(m_unEditPosition2>31)      //对位置值进行限值
								m_unEditPosition2=31;
							ucChar[0] &= 0xE0;    //将首字节的低5位置0
							ucChar[0] += m_unEditPosition2; //再加上位置值
							ucChar[3] = ucChar[0];    //同时计算校验值
							//第二字节
							unsigned char ucTemp=0x40;
							for(int i=0; i<6; i++)
							{
								if(strSwitchSetData.Mid(2+i,1)=="1")  
									ucChar[1] |= ucTemp;             
								else
									ucChar[1] &= (~ucTemp);
								ucTemp >>= 1;
							}
							ucChar[1] &= 0x7F; //前面做了那么多运算，用这条语句保证一下最高位为0
							ucChar[3] ^= ucChar[1];   //计算校验值
							////第三字节
							if(m_unEditVelocity2>120)
								m_unEditVelocity2=120;
							ucChar[2] = m_unEditVelocity2;
							ucChar[3] ^= ucChar[2];   //计算校验值
							////第四字节
							ucChar[3] &= 0x7F;
							CString strTemp1;
							strTemp=   _T("其通信内容为: ");
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
					//从'*'后收，flag=2,1次减1操作，正好将数据包的校验值保存在m_strChecksum2中
					flag--;  
				}
				else
					checksum= checksum^str[i_count];  //当flag<=0时，计算校验值
				break;
			}

		}
	}

	return 0;
}


void CMy1120112108LinHengDlg::SetSwitchStatus(unsigned int unSwitch, bool bStatus)
{
	if(bStatus)   //设置开关打开状态
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
	else     //设置开关关闭状态
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
	// TODO: 在此添加控件通知处理程序代码
	int nPortNo = m_ctrlComboPortNO2.GetCurSel()+1;
	m_CnComm2.Open(nPortNo);
	if(m_CnComm2.IsOpen())
	{
		//AfxMessageBox(_T("串口已经成功打开"));
		m_CnComm2.SetWnd(this->m_hWnd);
		m_bSerialPortOpened2=TRUE;
		m_unPort2=nPortNo; //用类成员变量记录打开的串口号，函数执行完后保留串口号
	}
	else
	{
		AfxMessageBox(_T("串口打开失败"));
		m_bSerialPortOpened2=false;
	}
	GetDlgItem(IDC_BUTTON_OPENPORT2)->EnableWindow(!m_bSerialPortOpened2);
	GetDlgItem(IDC_BUTTON_CLOSEPORT2)->EnableWindow(m_bSerialPortOpened2);
}


void CMy1120112108LinHengDlg::SendNMEAData(CString& strData)
{
	char checksum=0,cr=13,ln=10;
	char c1,c2; //2个 半Bype 校验值 
	for(int i=0;i<strData.GetLength();i++)
		checksum = checksum^strData[i];
	c2=checksum & 0x0F;	c1=((checksum >> 4) & 0x0F);
	if (c1 < 10) c1+= '0';	else c1 += 'A' - 10;
	if (c2 < 10) c2+= '0';	else c2 += 'A' - 10;
	CString strNMEAData;
	//加上包头，尾和校验值和回车换行符
	strNMEAData=_T("$")+ strData +_T("*")+c1+c2+cr+ln; 
	//以下几行程序关不通用，在自己的程序中注意修改
	m_CnComm.Write((LPCTSTR)strNMEAData);
	m_strEditTXDataInput.Format(_T("发送的数据包为：%s"),strNMEAData);
	UpdateData(FALSE);  //在发送显示编辑框中显示发送的数据包 
}
