// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108linheng_Client.h"
#include "MySocket.h"
#include "1120112108linheng_ClientDlg.h"


// MySocket

MySocket::MySocket()
{
}

MySocket::~MySocket()
{
}


// MySocket ��Ա����
void MySocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
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
	C1120112108linheng_ClientDlg* pDlg=(C1120112108linheng_ClientDlg*)AfxGetMainWnd(); //�õ������(�Ի���)ָ��
	pDlg->m_strRXDataTemp.Format("%s",chMsg);
	pDlg->UpdateRXData();   //�����Ի��Ľ��ձ༭������ʾ���յ�������

	CSocket::OnReceive(nErrorCode);
}
