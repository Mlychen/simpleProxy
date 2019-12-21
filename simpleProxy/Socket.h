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
	// 发送数据
	void sendData(const std::string& data);

	// 接受数据
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

	// 初始化套接字
	bool initSocket(short unsigned port);

	// 被动连接
	PrimySocket* waitConnect();

};

class TarSocket : public PrimySocket
{
public:
	TarSocket();
	~TarSocket();

	// 初始化套接字
	bool initSocket();

	// 主动连接
	PrimySocket* doConnect(const char* ip, short port);
};