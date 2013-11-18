// ListenSocket.cpp : 实现文件
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


// CListenSocket 成员函数
void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CAcceptSocket *pSocket=new CAcceptSocket;
	C1120112108linheng_ServerDlg * pDlg=(C1120112108linheng_ServerDlg*)AfxGetMainWnd(); //得到主框口(对话框)指针

	if(Accept(*pSocket))
	{
		pDlg->m_pAcceptList.AddTail(pSocket);
		CString strAddr,strAddr1;
		UINT unPort,unPort1;
		pSocket->GetPeerName(strAddr1,unPort1); //得到远程IP地址和端口号
		pSocket->GetSockName(strAddr,unPort);   //得到本地IP地址和端口号
		pDlg->m_strNetMsg.Format("本地IP%s端口%d\r\n连接上远程客户IP%s端口%d",
			strAddr,unPort,strAddr1,unPort1);
		pDlg->UpdateMsgData();
	}
	else
	{
		delete pSocket;
	}
	CSocket::OnAccept(nErrorCode);
}