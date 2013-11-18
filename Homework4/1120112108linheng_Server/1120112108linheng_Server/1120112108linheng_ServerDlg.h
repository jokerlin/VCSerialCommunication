
// 1120112108linheng_ServerDlg.h : ͷ�ļ�
//

#pragma once

#include "afxwin.h"
#include "CnComm.h"    //���CnComm��ͷ�ļ�
#include "ListenSocket.h"  //���CListenSocket��ͷ�ļ�


// C1120112108linheng_ServerDlg �Ի���
class C1120112108linheng_ServerDlg : public CDialogEx
{
// ����
public:
	C1120112108linheng_ServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SSERVER_1120101829_DIALOG };

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
	void UpdateMsgData();  //���ڸ�����������뷢����Ϣ
	CListenSocket* m_pListenSocket;
	BOOL m_bListened;  //���ڱ�־�������Ƿ��ڿ������������
	CPtrList m_pAcceptList; //���ڱ������socket�Ķ���
	CString  m_strNetMsg; //���ڴ��ݶ˿ںźͷ����IP��ַ
	BOOL m_bSerialPortOpened; //���ڱ�־�����Ƿ��
	CnComm m_MyComm; //����CSerialPort�����
	//	CString m_strSerialSendData; //����Ҫͨ�����ڷ��͵�����
	afx_msg void OnBnClickedButtonClear();
};