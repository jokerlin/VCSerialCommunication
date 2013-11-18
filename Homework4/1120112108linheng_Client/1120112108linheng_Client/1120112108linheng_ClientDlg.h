
// 1120112108linheng_ClientDlg.h : 头文件
//
#include "MySocket.h"

#pragma once


// C1120112108linheng_ClientDlg 对话框
class C1120112108linheng_ClientDlg : public CDialogEx
{
// 构造
public:
	C1120112108linheng_ClientDlg(CWnd* pParent = NULL);	// 标准构造函数

	BOOL m_bLinked;  //网络是否连接
	MySocket* m_pMySocket;
	//用于建立客户端
	CString m_strRXDataTemp;   //中间存储变量

// 对话框数据
	enum { IDD = IDD_SCLIENT_1120101829_DIALOG };

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
	CString m_strEditIPAddr;
	UINT m_unEditPortNO;
	CString m_strEditSendData;
	CString m_strEditRecvData;
	void UpdateRXData(void);
	afx_msg void OnBnClickedButtonLink();
	afx_msg void OnBnClickedButtonUnlink();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClear();
};
