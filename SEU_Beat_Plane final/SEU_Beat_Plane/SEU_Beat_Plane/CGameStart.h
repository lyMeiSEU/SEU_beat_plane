#pragma once
#include<windows.h>
#include <iostream>
#include "CPicture.h"

class GameStart
{
public:
	GameStart();
	~GameStart();

	
	void DrawMap(HWND);              //绘制画面
	void KeyDown(WPARAM);            //判断键盘
	void MouseMove(LPARAM);          //判断鼠标移动

	static void LoadMap();           //加载位图
 	static void SetGamestatus(int);  //设置游戏状态
	static int getGamestatus();      //获取游戏状态
	static void freeOption();        //释放指针
private:
	static Picture* Option[7];      //图片指针
	static int Gamestatus;          //游戏状态
};

