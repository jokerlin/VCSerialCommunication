// AcceptSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108linheng_Server.h"
#include "AcceptSocket.h"
#include "1120112108linheng_ServerDlg.h"

// CAcceptSocket

CAcceptSocket::CAcceptSocket()
{
}

CAcceptSocket::~CAcceptSocket()
{
}


// CAcceptSocket ��Ա����

// CAcceptSocket ��Ա����
void CAcceptSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char chMsg[5120], chMsgTemp[1024];
	UINT unRXCharNum;    //ÿ�ζ�ȡ���ַ���
	BOOL bEndFlag=0;   //������ϱ�־
	strcpy(chMsg,"");
	do
	{
		strcpy(chMsgTemp,"");
		unRXCharNum=Receive(chMsgTemp,1000);
		if(unRXCharNum>1000||unRXCharNum<=0)
		{
			AfxMessageBox("���������г���",MB_OK);
			return;
		}
		else if(unRXCharNum<1000 && unRXCharNum>0)
		{
			bEndFlag=1;
		}
		chMsgTemp[unRXCharNum]=0; //�����ַ�������λ
		strcat(chMsg,chMsgTemp);
	}while(bEndFlag==0);
	C1120112108linheng_ServerDlg* pDlg=(C1120112108linheng_ServerDlg*)AfxGetMainWnd(); //�õ������(�Ի���)ָ��
	pDlg->m_strNetMsg.Format("���յ���%s",chMsg);
	pDlg->UpdateMsgData();   //�����Ի��Ľ��ձ༭������ʾ����˿ڽ��յ�������
	CString strtemp;
	strtemp.Format("%s",chMsg);
	pDlg->SerialSendData(strtemp);
	strtemp="���������յ�:\r\n" + strtemp; //��ɻش���Ϣ
	Send(strtemp,strtemp.GetLength(),0); //���ͻش���Ϣ
	CSocket::OnReceive(nErrorCode);
}
