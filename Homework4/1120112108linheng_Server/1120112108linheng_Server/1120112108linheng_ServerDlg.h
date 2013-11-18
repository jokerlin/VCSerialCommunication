
// 1120112108linheng_ServerDlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include "CnComm.h"    //添加CnComm类头文件
#include "ListenSocket.h"  //添加CListenSocket类头文件


// C1120112108linheng_ServerDlg 对话框
class C1120112108linheng_ServerDlg : public CDialogEx
{
// 构造
public:
	C1120112108linheng_ServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SSERVER_1120101829_DIALOG };

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
	DECLARE_MESSAGE_MAP()
	
public:
	CComboBox m_ctrlComboComPort;
	CString m_strEditNetMsg;
	CString m_strEditComMsg;
	UINT m_unEditPortNO;
	CButton m_ctrlCheckSendData;

	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnCheckSenddata();

	void SerialSendData(CString strSendData);
	void UpdateMsgData();  //用于更新网络接收与发送信息
	CListenSocket* m_pListenSocket;
	BOOL m_bListened;  //用于标志服务器是否处于开启网络服务功能
	CPtrList m_pAcceptList; //用于保存接收socket的队列
	CString  m_strNetMsg; //用于传递端口号和服务的IP地址
	BOOL m_bSerialPortOpened; //用于标志串口是否打开
	CnComm m_MyComm; //定义CSerialPort类对象
	//	CString m_strSerialSendData; //定义要通过串口发送的数据
	afx_msg void OnBnClickedButtonClear();
};