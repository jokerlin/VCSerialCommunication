
// 1120112108linheng_ClientDlg.h : ͷ�ļ�
//
#include "MySocket.h"

#pragma once


// C1120112108linheng_ClientDlg �Ի���
class C1120112108linheng_ClientDlg : public CDialogEx
{
// ����
public:
	C1120112108linheng_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

	BOOL m_bLinked;  //�����Ƿ�����
	MySocket* m_pMySocket;
	//���ڽ����ͻ���
	CString m_strRXDataTemp;   //�м�洢����

// �Ի�������
	enum { IDD = IDD_SCLIENT_1120101829_DIALOG };

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
