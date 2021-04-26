#pragma once

#include "stdafx.h"

namespace Sis_
{
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

	//** 获取文件内容，用于小文件
	inline string GetFileContent(const string &filename)
	{
		string contents;

		ifstream finstream(filename);
		if (finstream)
		{
			contents.assign(istreambuf_iterator<char>(finstream), istreambuf_iterator<char>());
			finstream.close();
		}
		
		return contents;
	}

	//** 保存到文件，用于小文件
	inline int SaveToFile(const string &filename, const string &content)
	{
		ofstream foutstream(filename);
		if (foutstream)
		{
			foutstream << content;
			foutstream.close();
			return 0;
		}
		else
		{
			return -1;
		}
	}
}