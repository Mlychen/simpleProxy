#include "Proxy.h"
#include <string>
#include <thread>

Proxy::Proxy()
{

}

Proxy::~Proxy()
{

}

PrimySocket* Proxy::setTarget(const char* ip, const short port)
{
	tar.initSocket();
	return tar.doConnect(ip, port);
	printf("target connected\n");
}

void Proxy::src2tar(PrimySocket* src, PrimySocket* tar)
{
	std::string data;
	while (true)
	{
		src->recvData(data);
		if (src->mb_isWork == false)
		{
			printf("src2tar break\n");
			delete src;
			break;
		}

		tar->sendData(data);
	}
}

void Proxy::tar2src(PrimySocket* src, PrimySocket* tar)
{
	std::string data;
	while (true)
	{
		tar->recvData(data);
		if (tar->mb_isWork == false)
		{
			printf("tar2src break\n");
			delete tar;
			break;
		}
		src->sendData(data);
	}
}

void Proxy::run(const char* ip, const short sport, const short iport)
{
	src.initSocket(iport);

	while (true)
	{
		PrimySocket* srcpsok = src.waitConnect();
		PrimySocket* tarpsok = this->setTarget(ip, sport);

		printf("proxy runing\n");
		std::string data;

		std::thread t1(&Proxy::tar2src, srcpsok, tarpsok);
		std::thread t2(&Proxy::src2tar, srcpsok, tarpsok);

		t1.detach();
		t2.detach();
	}


}
