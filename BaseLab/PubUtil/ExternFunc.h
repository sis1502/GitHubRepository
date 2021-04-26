#pragma once

#include "stdafx.h"

namespace Sis_
{
	//** ��ȡ��ǰ����·��
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

	//** ��ȡ�ļ����ݣ�����С�ļ�
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

	//** ���浽�ļ�������С�ļ�
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