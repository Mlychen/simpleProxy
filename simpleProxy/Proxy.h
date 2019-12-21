#pragma once
#include "Socket.h"

class Proxy
{
public:
	Proxy();
	~Proxy();

	// ָ��ת��Ŀ���ַ
	PrimySocket* setTarget(const char* ip, const short port);

	// ��ȡԴ��
	static void src2tar(PrimySocket* src, PrimySocket* tar);

	// ��ȡĿ��
	static void tar2src(PrimySocket* src, PrimySocket* tar);

	// ת��
	void run(const char* ip, const short sport, const short iport);

	TarSocket tar;
	SrcSocket src;
};

