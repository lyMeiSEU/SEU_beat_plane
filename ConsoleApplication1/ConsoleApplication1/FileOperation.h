#pragma once

#ifndef __FileOperation_H__
#define __FileOperation_H__

#include <string>
using namespace std;

class FileOperation
{
public:
	// ���캯����dirΪ�ļ������ƣ���ע����ǩ�����⡢ģ�ͼ�������media�������
	FileOperation(string dir);
	~FileOperation(void);

	// ����һ���ļ���Ϊfilename���ļ�
	bool CreateFileW(string filename);

	// ɾ��һ���ļ���Ϊfilename���ļ�
	bool DeleteFile(string filename);

	// ��һ���ļ���Ϊfilename���ļ�����Ϊnewname
	bool AlterFileName(string filename, string newname);

protected:
	// �ж�Ŀ¼path�Ƿ����
	bool IsExisteDirectory(string path);

	// ����Ŀ¼
	string m_strPath;
};

#endif  // #ifndef __CFileOperation_H__