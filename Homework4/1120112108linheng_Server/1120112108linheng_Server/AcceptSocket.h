#pragma once

// CAcceptSocket ����Ŀ��

class CAcceptSocket : public CSocket
{
public:
	CAcceptSocket();
	virtual ~CAcceptSocket();
	virtual void OnReceive(int nErrorCode);
};


