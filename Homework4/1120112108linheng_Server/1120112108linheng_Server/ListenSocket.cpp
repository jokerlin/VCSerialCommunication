// ListenSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1120112108linheng_Server.h"
#include "ListenSocket.h"
#include "AcceptSocket.h"
#include "1120112108linheng_ServerDlg.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��Ա����
void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CAcceptSocket *pSocket=new CAcceptSocket;
	C1120112108linheng_ServerDlg * pDlg=(C1120112108linheng_ServerDlg*)AfxGetMainWnd(); //�õ������(�Ի���)ָ��

	if(Accept(*pSocket))
	{
		pDlg->m_pAcceptList.AddTail(pSocket);
		CString strAddr,strAddr1;
		UINT unPort,unPort1;
		pSocket->GetPeerName(strAddr1,unPort1); //�õ�Զ��IP��ַ�Ͷ˿ں�
		pSocket->GetSockName(strAddr,unPort);   //�õ�����IP��ַ�Ͷ˿ں�
		pDlg->m_strNetMsg.Format("����IP%s�˿�%d\r\n������Զ�̿ͻ�IP%s�˿�%d",
			strAddr,unPort,strAddr1,unPort1);
		pDlg->UpdateMsgData();
	}
	else
	{
		delete pSocket;
	}
	CSocket::OnAccept(nErrorCode);
}