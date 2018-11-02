#pragma once
#include <WINSOCK2.H>   
#include <cstdio>     
#include <iostream>
#include "CUserPlane.h" 

#pragma warning(disable:4996)
//���������ʹ�õĳ���      
#define SERVER_ADDRESS "127.0.0.1" //��������IP��ַ      
#define PORT           5150         //�������Ķ˿ں�      
#define MSGSIZE        1024         //�շ��������Ĵ�С      
#pragma comment(lib, "ws2_32.lib")   

class Connect
{
public:

	Connect();
	int GetBestScore();
	void SendScore(int score);
	~Connect();

private:

	WSADATA wsaData;
	//���������׽���  
	SOCKET sClient;
	//����Զ�̷������ĵ�ַ��Ϣ  
	SOCKADDR_IN server;
	//�շ�������      
	int UpScore;
	//�ɹ������ֽڵĸ���      
	int ret;
};



Connect::Connect() 
{    
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// �����ͻ����׽���      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻      
														 //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��      
	// ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0      
	server.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ      
	server.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //ָ�����ӷ�������IP��ַ      
														//�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ      
														//inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ      
	//�����ղ�ָ���ķ�������      
	connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN)); //���Ӻ������sClient��ʹ��������� 

																		//server������Զ�̷������ĵ�ַ��Ϣ   
}

int Connect::GetBestScore()
{
	
	char szMessage[MSGSIZE];
	int len = sizeof(SOCKADDR_IN);
	ret = recvfrom(sClient, szMessage, 100, 0, (sockaddr*)&sClient, &len);

	int score = 0;
	int i = 0;
	for(i=0;i<ret;++i)
	{
		score *= 10;
		score += (int)szMessage[i] - 48;
	}
	return score;
}

void Connect::SendScore(int score)
{
	UpScore = score;
	char s[20];
	sprintf(s, "%d", UpScore);
	if (s)
	{
		send(sClient, s, strlen(s)/**/, 0);
	}
	closesocket(sClient);
	WSACleanup();
}

Connect::~Connect()
{
	
}