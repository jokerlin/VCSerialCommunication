
// CMy1120112108LinHengDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CnComm.h"

// CMy1120112108LinHengDlg 对话框
class CMy1120112108LinHengDlg : public CDialogEx
{
// 构造
public:
	CMy1120112108LinHengDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_1120112108LinHeng_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnReceive(WPARAM port, LPARAM ch);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strEditRXDataDisp;
	CString m_strEditTXDataInput;
	CComboBox m_ctrlComboPortNO;  //第1个串口选择组合框控制变量
	CComboBox m_ctrlComboPortNO2; //第2个串口选择组合框控制变量
	BOOL m_bSerialPortOpened;   //用于标志第1个串口是否打开
	BOOL m_bSerialPortOpened2;   //用于标志第2个串口是否打开
	CnComm m_CnComm;    //第1个串口：CnComm类对象
	CnComm m_CnComm2;    //第2个串口：CnComm类对象
	HICON m_hIconRed;  //开启图标句柄
	HICON m_hIconOff; //关闭图标句柄
	UINT m_unPort1;   //记录第1个串口的串口号
	UINT m_unPort2;  //记录第2个串口的串口号
	CString m_strPortRXData;  //用于存储第1个串口收到的数据
	CString m_strPortRXData2;  //用于存储第2个串口收到的数据
	CString m_strCheckSum2;  //用于第2个串口接收数据计算检验值

	afx_msg void OnBnClickedButtonOpenport();
	afx_msg void OnBnClickedSenddata();
	afx_msg void OnBnClickedButtonCloseport();
	CStatic m_ctrlStaticIconS1;
	CStatic m_ctrlStaticIconS2;
	CStatic m_ctrlStaticIconS3;
	CStatic m_ctrlStaticIconS4;
	CStatic m_ctrlStaticIconS5;
	CStatic m_ctrlStaticIconS6;
	CStatic m_ctrlStaticIconS7;
	CStatic m_ctrlStaticIconS8;
	CButton m_ctrlCheckSwitch1;
	CButton m_ctrlCheckSwitch2;
	CButton m_ctrlCheckSwitch4;
	CButton m_ctrlCheckSwitch5;
	CButton m_ctrlCheckSwitch6;
	CButton m_ctrlCheckSwitch7;
	CButton m_ctrlCheckSwitch8;
	
	UINT m_unEditPosition;
	UINT m_unEditPosition2;
	UINT m_unEditVelocity;
	UINT m_unEditVelocity2;
	CString m_strEditDispData2;
	void SetSwitchStatus(unsigned int unSwitch, bool bStatus);
	bool GetSwitchStatus(unsigned int unSwitch);
	CButton m_ctrlCheckSwitch3;
	afx_msg void OnBnClickedButtonOpenport2();
	void SendNMEAData(CString& strData);
};

