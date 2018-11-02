#include "stdafx.h"
#include "CPicture.h"


#include<windows.h>
#include <iostream>


Picture::Picture() :
	CPi_hBitmap(NULL),
	CPi_TransColor(RGB(0, 0, 0)),
	CPi_nWidth(0),
	CPi_nHeight(0)
{
}

Picture::~Picture()
{
	FreeBitmap();
}


VOID Picture::FreeBitmap()
{
	if (CPi_hBitmap)
		DeleteObject(CPi_hBitmap);
}

VOID Picture::LoadBitmap(LPCTSTR lpszName, UINT Color, int w, int h)//加载位图（文件名，需要透明化的背景颜色，位图宽，位图高）
{
	CPi_nWidth = w;
	CPi_nHeight = h;
	CPi_TransColor = Color;
	if (CPi_hBitmap)
	{
		DeleteObject(CPi_hBitmap);
	}
	CPi_hBitmap = (HBITMAP)LoadImage(NULL, lpszName, IMAGE_BITMAP, CPi_nWidth, CPi_nHeight, LR_LOADFROMFILE);//加载位图

}

VOID Picture::DrawBitmap(HWND hWnd, int xoriginDest, int yoriginDest, int wDest, int hDest, int xoriginSrc, int yoriginSrc)//绘制背景透明图
{
	HDC ghdc = GetDC(hWnd);
	HDC g_mdc = CreateCompatibleDC(ghdc);//建立兼容DC
	SelectObject(g_mdc, CPi_hBitmap);//选用位图对象
	TransparentBlt(ghdc, xoriginDest, yoriginDest, wDest, hDest, g_mdc, xoriginSrc, yoriginSrc, CPi_nWidth, CPi_nHeight, CPi_TransColor);
	//贴图函数（设备环境句柄，目的矩形X坐标，目的矩形Y，目标宽，目标高，原设备环境句柄，原矩形X坐标，Y，原矩形宽，高，RGB颜色值）
	ReleaseDC(hWnd, ghdc);
	DeleteDC(g_mdc);
	DeleteDC(ghdc);
}

