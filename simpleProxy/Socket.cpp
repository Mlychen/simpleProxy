#include "Socket.h"


PrimySocket::PrimySocket()
{
	m_cfd = -1;
	m_lfd = -1;
	mb_isWork = false;
}

PrimySocket::~PrimySocket()
{
}

bool PrimySocket::InitNet()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return false;
	}
	return true;
}

void PrimySocket::sendData(const std::string& data)
{
	send(m_cfd, data.data(), data.size(), 0);
	//printf("len:%ld send:%s\n", data.length(), data.c_str());
}

void PrimySocket::recvData(std::string& data)
{
	char buf[BUFSIZE] = { 0 };
	int res;
	res = recv(m_cfd, buf, sizeof(buf), 0);
	if (res <= 0)
	{
		mb_isWork = false;
	}
	else
	{
		data.resize(0);
		data.append(buf, res);


		//printf("len:%ld recv:%s\n", data.length(), data.c_str());
	}

}


SrcSocket::SrcSocket()
{

}


SrcSocket::~SrcSocket()
{
}

bool SrcSocket::initSocket(short unsigned port)
{
	printf("src port:%d\n", port);
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	m_lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_lfd < 0)
	{
		perror("socket");
		return false;
	}

	int ret = bind(m_lfd, (sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("src bind");
		return false;
	}
	ret = listen(m_lfd, 10);
	if (ret < 0)
	{
		perror("src listen");
		return false;
	}

	printf("src socket init over\n");
	return true;
}

PrimySocket* SrcSocket::waitConnect()
{
	printf("wait connect\n");
	PrimySocket* psok = new PrimySocket();
	sockaddr_in addr;
	int len = sizeof(addr);

	memset(&addr, 0, sizeof(addr));
	m_cfd = accept(m_lfd, (sockaddr*)&addr, &len);
	if (m_cfd < 0)
	{
		perror("accept");
		return false;
	}


	psok->mb_isWork = true;
	psok->m_cfd = m_cfd;

	printf("got connect\n");
	return psok;
}



TarSocket::TarSocket()
{
}

TarSocket::~TarSocket()
{
}

bool TarSocket::initSocket()
{
	m_cfd = socket(AF_INET, SOCK_STREAM, 0);
	return true;
}

PrimySocket* TarSocket::doConnect(const char* ip, short port)
{
	PrimySocket* psok = new PrimySocket();
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	printf("before connect.. ip:%s,port:%d\n", ip, port);
	int ret = connect(m_cfd, (sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("connect");
		return false;
	}

	psok->m_cfd = m_cfd;
	psok->mb_isWork = true;
	return psok;
}

