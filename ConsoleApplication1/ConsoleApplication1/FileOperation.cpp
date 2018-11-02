#include "pch.h"
#include <fstream>
#include <io.h>
#include "FileOperation.h"

#pragma warning(disable : 4996)

FileOperation::FileOperation(string dir)
{
	// ��m_strPath����ֵ
	string path = _pgmptr;  // exe�ļ�����Ŀ¼����*.exe
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
	// ɾ���ļ����ɹ�����0�����򷵻�-1
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
	// �����ļ���,�ɹ�����0�����򷵻�-1
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