#pragma once
#include "Socket.h"

class Proxy
{
public:
	Proxy();
	~Proxy();

	// 指定转发目标地址
	PrimySocket* setTarget(const char* ip, const short port);

	// 读取源端
	static void src2tar(PrimySocket* src, PrimySocket* tar);

	// 读取目标
	static void tar2src(PrimySocket* src, PrimySocket* tar);

	// 转发
	void run(const char* ip, const short sport, const short iport);

	TarSocket tar;
	SrcSocket src;
};

