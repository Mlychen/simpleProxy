#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <WinSock2.h>

#define BUFSIZE 1024

class PrimySocket
{
public:
	PrimySocket();
	~PrimySocket();

	static bool InitNet();
	// ��������
	void sendData(const std::string& data);

	// ��������
	void recvData(std::string& data);


	SOCKET m_lfd;
	SOCKET m_cfd;
	bool mb_isWork;
};


class SrcSocket : public PrimySocket
{
public:
	SrcSocket();
	~SrcSocket();

	// ��ʼ���׽���
	bool initSocket(short unsigned port);

	// ��������
	PrimySocket* waitConnect();

};

class TarSocket : public PrimySocket
{
public:
	TarSocket();
	~TarSocket();

	// ��ʼ���׽���
	bool initSocket();

	// ��������
	PrimySocket* doConnect(const char* ip, short port);
};