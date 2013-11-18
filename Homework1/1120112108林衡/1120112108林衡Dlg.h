
// 1120112108林衡Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CnComm.h"

// CMy1120112108林衡Dlg 对话框
class CMy1120112108林衡Dlg : public CDialogEx
{
// 构造
public:
	CMy1120112108林衡Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY1120112108_DIALOG };

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
	CString m_streditRXDATADISP;
	CString m_streditTXDATAINPUT;
	CComboBox m_ctrlcomboPORTNO;
	afx_msg void OnCbnSelchangeComboPortno();
	bool m_bSerialPortOpened;
	CnComm m_CnComm;
	afx_msg void OnBnClickedButtonOpenport();
	afx_msg void OnBnClickedButtonSenddata();
	afx_msg void OnBnClickedButtonCloseport();
	LRESULT OnReceive(WPARAM port, LPARAM ch);
	afx_msg void OnBnClickedButtonEmptySendbox();
	afx_msg void OnBnClickedButtonEmptyrexbox();
	CComboBox m_ctrlcomboBAUDRATE;
	CComboBox m_ctrlcomboBYTESIZES;
	CComboBox m_ctrlcomboSTOPBITS;
};
