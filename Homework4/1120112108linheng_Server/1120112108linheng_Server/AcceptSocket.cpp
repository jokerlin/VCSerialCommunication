// AcceptSocket.cpp : 实现文件
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


// CAcceptSocket 成员函数

// CAcceptSocket 成员函数
void CAcceptSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char chMsg[5120], chMsgTemp[1024];
	UINT unRXCharNum;    //每次读取的字符数
	BOOL bEndFlag=0;   //接收完毕标志
	strcpy(chMsg,"");
	do
	{
		strcpy(chMsgTemp,"");
		unRXCharNum=Receive(chMsgTemp,1000);
		if(unRXCharNum>1000||unRXCharNum<=0)
		{
			AfxMessageBox("接收数据中出错",MB_OK);
			return;
		}
		else if(unRXCharNum<1000 && unRXCharNum>0)
		{
			bEndFlag=1;
		}
		chMsgTemp[unRXCharNum]=0; //加上字符串结束位
		strcat(chMsg,chMsgTemp);
	}while(bEndFlag==0);
	C1120112108linheng_ServerDlg* pDlg=(C1120112108linheng_ServerDlg*)AfxGetMainWnd(); //得到主框口(对话框)指针
	pDlg->m_strNetMsg.Format("接收到：%s",chMsg);
	pDlg->UpdateMsgData();   //在主对话的接收编辑框中显示网络端口接收到的数据
	CString strtemp;
	strtemp.Format("%s",chMsg);
	pDlg->SerialSendData(strtemp);
	strtemp="服务器已收到:\r\n" + strtemp; //组成回传信息
	Send(strtemp,strtemp.GetLength(),0); //发送回传信息
	CSocket::OnReceive(nErrorCode);
}
