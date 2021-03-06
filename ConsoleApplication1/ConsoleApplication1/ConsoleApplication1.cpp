// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <WINSOCK2.H>   
#include <stdio.h>     
using namespace std;
#include "FileOperation.h"


#pragma warning(disable:4996)

#define PORT           5150    
#define MSGSIZE        1024    

#pragma comment(lib, "ws2_32.lib")      

int main()
{
	long int MostScore = 10;
	WSADATA wsaData;
	SOCKET sListen;
	SOCKET sClient;
	SOCKADDR_IN local;
	SOCKADDR_IN client;

	FileOperation FileOperator("\\Data");
	FileOperator.CreateFile("Data.txt");

	char szMessage[MSGSIZE];
	int ret;
	int iaddrSize = sizeof(SOCKADDR_IN);

	WSAStartup(0x0202, &wsaData);

	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN));
	
up:
	listen(sListen, 1);

	sClient = accept(sListen, (struct sockaddr *) &client, &iaddrSize);
	printf_s("Accepted client:%s:%d\n", inet_ntoa(client.sin_addr),
		ntohs(client.sin_port));
	int len = sizeof(SOCKADDR_IN);
	
	long int score = MostScore;
	int n = 0;
	char s[20];
	while (score != 0) 
	{
		s[n] = score % 10;
		score /= 10;
		n++;
	}
	s[n] = '\0';
	sprintf(s, "%d", MostScore);

	send(sClient, s, strlen(s), 0);
	
	while (TRUE)
	{    
		
		ret = recvfrom(sClient, szMessage, 100, 0, (sockaddr*)&client, &len);
		
		if (ret > 0) 
		{
			long int score = 0;
			int i;
			for (i = 0; i < ret; i++)
			{
				score *= 10;
				score += szMessage[i] - 48;
			}
			if (score >= MostScore)
			{
				MostScore = score;
			}

			szMessage[ret] = '\0';
			printf("Received [%d bytes]: '%s'\n", ret, szMessage);

			ofstream outfile("Data.txt", ios::app);//ios::app表示在原文件末尾追加 

			if (!outfile) {

				cout << "Open the file failure...\n";

				exit(0);

			}

			outfile << "ip = " << inet_ntoa(client.sin_addr) << " port = " << ntohs(client.sin_port) << " Score =" << szMessage << "\n";//向文件写数据 
			string User;

			outfile.close();
			
			client.sin_addr = { 204,204,204,204 };
			goto up;
		}
	}

	
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
