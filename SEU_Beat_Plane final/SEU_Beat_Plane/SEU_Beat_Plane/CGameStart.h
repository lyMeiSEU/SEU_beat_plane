#pragma once
#include<windows.h>
#include <iostream>
#include "CPicture.h"

class GameStart
{
public:
	GameStart();
	~GameStart();

	
	void DrawMap(HWND);              //���ƻ���
	void KeyDown(WPARAM);            //�жϼ���
	void MouseMove(LPARAM);          //�ж�����ƶ�

	static void LoadMap();           //����λͼ
 	static void SetGamestatus(int);  //������Ϸ״̬
	static int getGamestatus();      //��ȡ��Ϸ״̬
	static void freeOption();        //�ͷ�ָ��
private:
	static Picture* Option[7];      //ͼƬָ��
	static int Gamestatus;          //��Ϸ״̬
};

