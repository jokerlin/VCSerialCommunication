#pragma once

// MySocket ����Ŀ��

class MySocket : public CSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnReceive(int nErrorCode);
};


