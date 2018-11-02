#pragma once

#ifndef __FileOperation_H__
#define __FileOperation_H__

#include <string>
using namespace std;

class FileOperation
{
public:
	// 构造函数，dir为文件夹名称：标注、书签、试题、模型及动画、media、界面等
	FileOperation(string dir);
	~FileOperation(void);

	// 创建一个文件名为filename的文件
	bool CreateFileW(string filename);

	// 删除一个文件名为filename的文件
	bool DeleteFile(string filename);

	// 将一个文件名为filename的文件更名为newname
	bool AlterFileName(string filename, string newname);

protected:
	// 判断目录path是否存在
	bool IsExisteDirectory(string path);

	// 工作目录
	string m_strPath;
};

#endif  // #ifndef __CFileOperation_H__