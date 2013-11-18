
// CMy1120112108LinHengDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CnComm.h"

// CMy1120112108LinHengDlg �Ի���
class CMy1120112108LinHengDlg : public CDialogEx
{
// ����
public:
	CMy1120112108LinHengDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_1120112108LinHeng_DIALOG };

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
	LRESULT OnReceive(WPARAM port, LPARAM ch);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strEditRXDataDisp;
	CString m_strEditTXDataInput;
	CComboBox m_ctrlComboPortNO;  //��1������ѡ����Ͽ���Ʊ���
	CComboBox m_ctrlComboPortNO2; //��2������ѡ����Ͽ���Ʊ���
	BOOL m_bSerialPortOpened;   //���ڱ�־��1�������Ƿ��
	BOOL m_bSerialPortOpened2;   //���ڱ�־��2�������Ƿ��
	CnComm m_CnComm;    //��1�����ڣ�CnComm�����
	CnComm m_CnComm2;    //��2�����ڣ�CnComm�����
	HICON m_hIconRed;  //����ͼ����
	HICON m_hIconOff; //�ر�ͼ����
	UINT m_unPort1;   //��¼��1�����ڵĴ��ں�
	UINT m_unPort2;  //��¼��2�����ڵĴ��ں�
	CString m_strPortRXData;  //���ڴ洢��1�������յ�������
	CString m_strPortRXData2;  //���ڴ洢��2�������յ�������
	CString m_strCheckSum2;  //���ڵ�2�����ڽ������ݼ������ֵ

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

