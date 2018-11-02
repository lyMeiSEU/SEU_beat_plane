#include "pch.h"
#include <fstream>
#include <io.h>
#include "FileOperation.h"

#pragma warning(disable : 4996)

FileOperation::FileOperation(string dir)
{
	// 给m_strPath赋初值
	string path = _pgmptr;  // exe文件所在目录，带*.exe
	m_strPath = path.substr(0, path.find_last_of('\\') + 1);
	m_strPath += dir;

	if (!IsExisteDirectory(m_strPath))
	{
		string str = "md \"" + m_strPath + "\"";
		system(str.c_str());
	}
}


FileOperation::~FileOperation(void)
{
}


bool FileOperation::CreateFileW(string filename)
{
	string path = m_strPath + '\\' + filename;
	fstream file;
	file.open(path, ios::out);
	if (!file)
	{
		return false;
	}
	file.close();

	return true;
}


bool FileOperation::DeleteFile(string filename)
{
	string path = m_strPath + '\\' + filename;
	// int remove(char *filename);
	// 删除文件，成功返回0，否则返回-1
	if (-1 == remove(path.c_str()))
	{
		return false;
	}

	return true;
}


bool FileOperation::AlterFileName(string filename, string newname)
{
	string path = m_strPath + '\\' + filename;
	newname = m_strPath + '\\' + newname;
	// int rename(char *oldname, char *newname);
	// 更改文件名,成功返回0，否则返回-1
	if (-1 == rename(path.c_str(), newname.c_str()))
	{
		return false;
	}

	return true;
}

bool FileOperation::IsExisteDirectory(string path)
{
	if (-1 != _access(path.c_str(), 0))
	{
		return true;
	}
	return false;
}