#include <iostream>
#include "Proxy.h"
#include <thread>

void test1();
void test2();
short bindPort = 1002;


int main(int args, char* argv[])
{

	char* ip, * port, * i_port;
	ip = nullptr;
	port = nullptr;
	i_port = nullptr;
	if (args < 7)
	{
		return EXIT_FAILURE;
	}
	for (int i = 1; i < 6; ++i)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'p')
			{
				port = argv[++i];
			}
			else if (argv[i][1] == 'a')
			{
				ip = argv[++i];
			}
			else if (argv[i][1] == 'i')
			{
				i_port = argv[++i];
			}
			else
			{
				return EXIT_FAILURE;
			}
		}
	}
	if (ip == nullptr)
	{
		return EXIT_FAILURE;
	}
	if (port == nullptr)
	{
		return EXIT_FAILURE;
	}
	if (i_port == nullptr)
	{
		return EXIT_FAILURE;
	}

	int iport1 = 0;
	int iport2 = 0;
	for (int i = 0; i < 6; ++i)
	{
		if (port[i] == '\0')
		{
			break;
		}
		iport1 = (port[i] - '0') + iport1 * 10;
	}
	for (int i = 0; i < 6; ++i)
	{
		if (i_port[i] == '\0')
		{
			break;
		}
		iport2 = (i_port[i] - '0') + iport2 * 10;
	}
	if (iport1 > 65535 && iport2 > 65535)
	{
		return EXIT_FAILURE;
	}
	if (iport1 < 1 && iport2 < 1)
	{
		return EXIT_FAILURE;
	}

	printf("ip:%s\tport:%d\ti_port:%d\n", ip, iport1, iport2);


	std::cout << "hello world" << std::endl;
	PrimySocket::InitNet();

	Proxy p;
	p.run(ip, (short)iport1, (short unsigned)iport2);

	char ch = getchar();
	return EXIT_SUCCESS;
}

void test1()
{
	SrcSocket test;
	std::string data;
	test.initSocket(bindPort);
	test.waitConnect();
	test.recvData(data);
	std::cout << data << std::endl;
}

void test2()
{
	TarSocket test;
	std::string data("hello");
	std::cout << data << std::endl;
	test.initSocket();
	test.doConnect("127.0.0.1", 2000);
	test.sendData(data);
}
