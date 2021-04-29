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

	//** ��ʮ��������ʽ��ӡunsigned char[]
	inline void DisplayUnsignedcharInHex(const unsigned char *arr, const int &len, const char *name = nullptr)
	{
		cout << "Unsigned Char (HEX) >> ";

		if (name)
		{
			cout << name << ":";
		}

		for (int i = 0; i < len; i++)
		{
			//cout << hex << setfill('0') << setw(2) << (unsigned int)arr[i] << " ";
			printf("%x ", arr[i]);
		}
		cout << endl;
	}

	//** ���ַ���ʽ��ӡunsigned char[]
	inline void DisplayUnsignedcharInChar(const unsigned char *arr, const int &len, const char *name = nullptr)
	{
		cout << "Unsigned Char (CHAR) >> ";

		if (name)
		{
			cout << name << ":";
		}

		for (int i = 0; i < len; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	//** ��ʮ��������ʽ��ӡchar[]
	inline void DisplayCharInHex(const char *arr, const int &len, const char *name = nullptr)
	{
		cout << "Char (HEX) >> ";

		if (name)
		{
			cout << name << ":";
		}

		for (int i = 0; i < len; i++)
		{
			//cout << hex << setfill('0') << setw(2) << (unsigned int)(unsigned char)arr[i] << " ";
			printf("%x ", arr[i]);
		}
		cout << endl;
	}
}