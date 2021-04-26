#pragma once

#include "PubUtil/BaseDef.h"

namespace Sis_
{
	//** 检查地址格式
	inline string CheckIP(const char *ip)
	{
		if (ip == nullptr || strlen(ip) == 0)
		{
			return string("null string");
		}

		struct in_addr addr;
		if (inet_pton(AF_INET, ip, &addr) > 0)
		{
			return string("ipv4");
		}
		else
		{
			struct in6_addr addr;
			if (inet_pton(AF_INET6, ip, &addr) > 0)
			{
				return string("ipv6");
			}
			else
			{
				return string("error srting");
			}
		}
	}

	//** 获取当前运行路径
	inline string GetRunningDirectory()
	{
		string dir = "";

#	ifdef _WIN32
		char path[MAX_PATH] = { 0 };
		DWORD ret = GetModuleFileNameA(nullptr, path, MAX_PATH);
		if (ret <= 0)
		{
			cout << "[ExternFunc][GetRunningDirectory]ret:" << ret << endl;
		}
		else
		{
			dir = string(path).substr(0, string(path).rfind("\\") + 1);
			cout << "[ExternFunc][GetRunningDirectory]dir:" << dir << endl;
		}
#	else
		//...
#	endif

		return dir;
	}

	inline string GetFileContent(const string &filename)
	{
		std::string contents;

		std::ifstream finstream(filename);
		contents.assign(std::istreambuf_iterator<char>(finstream), std::istreambuf_iterator<char>());
		finstream.close();

		return contents;
	}
}