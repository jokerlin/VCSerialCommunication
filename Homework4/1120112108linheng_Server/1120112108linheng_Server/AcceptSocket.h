#pragma once

// CAcceptSocket ÃüÁîÄ¿±ê

class CAcceptSocket : public CSocket
{
public:
	CAcceptSocket();
	virtual ~CAcceptSocket();
	virtual void OnReceive(int nErrorCode);
};


