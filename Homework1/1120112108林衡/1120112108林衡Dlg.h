
// 1120112108�ֺ�Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CnComm.h"

// CMy1120112108�ֺ�Dlg �Ի���
class CMy1120112108�ֺ�Dlg : public CDialogEx
{
// ����
public:
	CMy1120112108�ֺ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY1120112108_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
